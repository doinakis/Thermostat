/*
Doinakis Michalis
e-mail: doinakis@ece.auth.gr
AEM : 9292
*/
#include "Thermostat.h"

volatile int lcd_flag = 0;																			// Flag to time the lcd on/off
volatile int lcd_active_count = 0;															// Seconds the lcd is active
volatile int temp_ready_flag = 0;																// Flag that indicates all the 24 measurements have been taken 
volatile int get_temp_flag = 0;																	// Flag that indicates 5 seconds have passed, time to take the measurement
volatile int temp_count = 0; 																		// Counts how many seconds passed max value 5
volatile float mean_temp = 0;																		// Sum of all the 24 measurements
volatile float last_temp = 0;																		// Most recent temp taken 
volatile float last_mean_temp = 0;															// Mean of the 24 measurements

int main(void){
	
	volatile float distance = 0;																	// Variable to store the measured distance
	int counter = 0;																							// Coutner to indicate 24 measurments were taken
	thermostat_init();																						// Initialize the requiered peripherals for the thermostat to work
	char buff[16];																								// Buffer in order to print the messages to the lcd
	last_temp = read_temp();
	timer_enable();																								// Enable the timer
	
	while(1){
		lcd_clear();																								// Always clear the lcd first from the previous state
		lcd_set_cursor(0,0);																				// Set the cursor to the row first column
		
		// Get a measurement 
		if(get_temp_flag){																					// If get_temp_flag, it means that 5 seconds have passed and its time to get a measurement
			timer_disable();																					// Disable the timer while the measurement is being taken 
			counter++;																								// Increase the number of taken measurements by one 
			last_temp = read_temp();																	// Take the measurement
			mean_temp = mean_temp + last_temp;												// Add the temperature to the previous ones 
			get_temp_flag = 0;																				// Set the flag back to zero again 
			if(counter == 24){																				// If the measurement was the 24th 
				temp_ready_flag =1;																			// then its time to preview the mean to the lcd, so set the temp_ready_flag = 1 
			}
			timer_enable();																						// Enable the timer before exiting the if statement
		}
		
		// Display the mean value 
		if(temp_ready_flag){																				// If the mean value is ready 
			timer_disable();																					// Disable the timer while the mean is being displayed on the lcd
			gpio_set(Screen,1);																				// Light the screen backlight 
			last_mean_temp = mean_temp/24;														// Calculate the mean		
			timer_enable();																						// Enable the timer 
			// Prepare for the next 24 values
			counter = 0;																							// Set the counter for the 24 values back to 0 
			temp_count = 0;																						// Set the temp_count coutner back to 0 
			mean_temp = 0;																						// Set the mean_temp variable back to 0 
		  get_temp_flag = 0;																				// Set get_temp_flag back to 0 
			
			// Lcd Update
			lcd_flag = 1;																							// Set the Lcd update flag to one 
			lcd_clear();																							// Clear the Lcd and put the cursor to the first line and first row
			lcd_set_cursor(0,0);
			sprintf(buff,"Mean: %.4f %cC" ,last_mean_temp,0xDF);			// Write the desirable diplay text into buffer 
			lcd_print(buff);																					// Display it to the lcd for 10 seconds
			while(lcd_active_count < 100);														
			
			// Lcd Disable 
			lcd_flag = 0;																							// Set the Lcd update flag to zero 
			lcd_active_count = 0;																			// Set the Lcd active count (second active) to 0 
			temp_ready_flag = 0;																			// Set the temp_ready_flag to 0 
			gpio_set(Screen,0);																				// Turn the screen backlight off
		}
		
		// Display Low temperature warning 
		if(last_temp < Low_Temp){																		// Check if the last taken temperature is below a certain theshold

			gpio_set(Low_Temp_Pin,1);																	// Light up the blue Led
			
			// Lcd Update
			gpio_set(Screen,1);																				// Turn the screen backlight on
			lcd_flag = 1;																							// Set the Lcd update flag to one
			lcd_clear();																							// Clear the Lcd and put the cursor to the first line and first row
			lcd_set_cursor(0,0);
			sprintf(buff,"Low_Temp:%.3f%c" ,last_temp,0xDF);					// Write the desirable diplay text into buffer
			lcd_print(buff);																					// Display it to the lcd for 5 seconds
			while(lcd_active_count < 50);
			
			// Lcd Disable
			lcd_flag = 0;																							// Set the Lcd update flag to zero
			lcd_active_count = 0;																			// Set the Lcd active count (second active) to 0 
			gpio_set(Screen,0);																				// Turn the screen backlight off
		}else{
			gpio_set(Low_Temp_Pin,0);																	// If the temperature is higher the Led is off
		}
		
		// Display Low temperature warning
		if(last_temp > High_Temp){																	// Check if the last taken temperature is higher a certain theshold
			
			gpio_set(High_Temp_Pin,1);																// Light up the red Led
			gpio_set(Fan_Pin,1);																			// Light the fan pin (turn on a Fan)
			// Lcd update 
			gpio_set(Screen,1);																				// Turn the screen backlight on
			lcd_flag = 1;																							// Set the Lcd update flag to one
			lcd_clear();																							// Clear the Lcd and put the cursor to the first line and first row
			lcd_set_cursor(0,0);
			sprintf(buff,"HighTemp:%.3f%c" ,last_temp,0xDF);					// Write the desirable diplay text into buffer
			lcd_print(buff);
			lcd_set_cursor(0,1);
			sprintf(buff,"Fan On");																		// Write the desirable diplay text into buffer
			lcd_print(buff);
			while(lcd_active_count < 50);															// Display it to the lcd for 5 seconds
			
			// Lcd Disable
			lcd_flag = 0;																							// Set the Lcd update flag to zero
			lcd_active_count = 0;																			// Set the Lcd active count (second active) to 0
			gpio_set(Screen,0);																				// Turn the screen backlight off
		}else{
			gpio_set(High_Temp_Pin,0);																// If the temperature is lower the Led is off
			gpio_set(Fan_Pin,0);																			// Set the fan Led to off (close the fan)
		}
		
		// Check if a subject is nearbry (taking into consideration the defined threshold)
		distance = ultrasonic_dist();																// Get the distance measurement
		if (distance < threshold){ 																	// If its lower thant the threshold 
			
			// Lcd update 
			gpio_set(Screen,1);																				// Turn the screen backlight on
			lcd_flag = 1;																							// Set the Lcd update flag to one
			lcd_clear();																							// Clear the Lcd and put the cursor to the first line and first row
			lcd_set_cursor(0,0);
			
			sprintf(buff,"Temp: %.4f %cC" ,last_temp,0xDF);						// Write the desirable diplay text into buffer
			lcd_print(buff);
			lcd_set_cursor(0,1);																			// Set cursor to the next line 
			sprintf(buff,"Mean: %.4f %cC" ,last_mean_temp,0xDF);			// Write the desirable diplay text into buffer
			lcd_print(buff);
			while(lcd_active_count < 50);															// Display it to the lcd for 5 seconds
			
			// Lcd Disable
			lcd_flag = 0;																							// Set the Lcd update flag to zero
			lcd_active_count = 0;																			// Set the Lcd active count (second active) to 0
			gpio_set(Screen,0);																				// Turn the screen backlight off
		}
	}
}


