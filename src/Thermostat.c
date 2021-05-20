/*
Doinakis Michalis
e-mail: doinakis@ece.auth.gr
AEM : 9292
*/
#include "Thermostat.h"



void timer_handler(void){
	
	if(lcd_flag){														// If the lcd flag == 1 then it starts counting how many seconds the lcd was active 
		lcd_active_count++;
	}
	if(!temp_ready_flag){										// If 24 measurements are not completed yet 
		
			 
		
		if(temp_count%50 == 0){								// If 5  seconds have passed
			get_temp_flag = 1;									// Set the get_temp_flag to 1 to indicate that a new measurement needs to be taken 
		}
		temp_count++;													// Count how many seconds have passed 	
	}
}

void thermostat_init(void){
	
	lcd_init();															// Initialize the lcd 			
	gpio_set_mode(Screen, Output);	 				// Initialize the leds as output
	gpio_set_mode(Low_Temp_Pin, Output);
	gpio_set_mode(High_Temp_Pin, Output);
	gpio_set_mode(Fan_Pin, Output);
	gpio_set(Screen,0);											// Set backlight pin to 0 
	gpio_set(Low_Temp_Pin,0);								// Set the leds to 0
	gpio_set(High_Temp_Pin,0);
	gpio_set(Fan_Pin,0);
	prox_sens_init();												// Initialize the proximity sensor
	timer_init(SystemCoreClock/10);					// Initialize the timer to issue an interrupt every 0.1 seconds
	timer_set_callback(timer_handler);			// Set the timer interrupt handler
	
}
