/*
Doinakis Michalis
e-mail: doinakis@ece.auth.gr
AEM : 9292
*/
#include "temp_sens.h"


uint8_t start_temp_sens(void){
	
	uint8_t response = 0;									// Initialize return value 
	gpio_set_mode(Temp_Pin,Output);				// Set the pin mode to output 
	
	gpio_set(Temp_Pin, Reset);						// Reset the pin : set it to 0 
	delay_us(480);												// Delay for at least 480 us
	
	gpio_set_mode(Temp_Pin, Input);				//Set the pin as input 
	delay_us(80);													// Delay for at least 80 us
	
	if (!gpio_get(Temp_Pin)){
		response = 1;												// If the pin is low then the sensor is detected
	}else{
		response = -1;											// else the response is set to -1 to indicate no sensor is detected
	}
		delay_us(400);											// Delay for at least 480 us totally
	
	return response;

}

void write_temp_sens(uint8_t data){
	
	gpio_set_mode(Temp_Pin,Output);				// Set the pin as output 
	
	for (int i=0; i<8; i++){							// For every bit in the data variable 
		
		if ((data &(1<<i))!=0){							// If the bit is high 
			// Write 1 to the sensor 
			gpio_set_mode(Temp_Pin,Output);		// Set the pin as output 
			gpio_set(Temp_Pin, Reset);				// Reset the pin : set it to 0 
			delay_us(1);											// Delay for 1 us 
			gpio_set_mode(Temp_Pin, Input);		// Set the pin as input 
			delay_us(60);											// Delay for 60 us 
			
		}else{															// else if   the bit is low 
			// Write 0 to the sensor 
			gpio_set_mode(Temp_Pin,Output);		// Set the pin as output
			gpio_set(Temp_Pin, Reset);				// Reset the pin : set it to 0 
			delay_us(60);											// Delay for 60 us 
			gpio_set_mode(Temp_Pin, Input);		// Set the pin as input
			
		}
	}
}

uint8_t read_temp_sens(void)
{
	uint8_t value=0;											// Initialize return value 
	gpio_set_mode(Temp_Pin, Input); 			// Set the pin as Input 

	for (int i=0;i<8;i++){								// For every bit to be returned 
		
		gpio_set_mode(Temp_Pin,Output);			// Set the pin as output
		gpio_set(Temp_Pin, Reset);					// Reset the pin : set it to 0 
		delay_us (2);												// Delay for 2 us 
		gpio_set_mode(Temp_Pin, Input);			// Set the pin as input 
		if (gpio_get(Temp_Pin)){						// If the pin is high 
			
			value |= 1<<i;										// store 1 to the i-th bit 
			
		}
		delay_us (60);											// Delay for 60 us 
	}
	return value;													// Return read data 
}
float read_temp(void){
	
	float temp;														// Initialize return value 
	
	// Variables to store the temperature data 
	uint8_t  Temp_byte1; 
	uint8_t  Temp_byte2;
	start_temp_sens();											// Initialize the sensor 
	delay_us(1);														// Delay for 1 us 
	write_temp_sens(SKIP_ROM); 							// Skip ROM
	write_temp_sens(CONVERT_T); 						// Convert t
	delay_us (800);													// Delay for 800 us 

	start_temp_sens();											// Initialize the sensor again 
	delay_us(1);														// Delay for 1 us 
	write_temp_sens(SKIP_ROM);							// Skip ROM
	write_temp_sens(READ_SCRATCHPAD);				// Read Scratch-pad
	Temp_byte1 = read_temp_sens();					// Read the first byte from the sensor 
	Temp_byte2 = read_temp_sens();					// Read the second byte from the sensor
	temp = (Temp_byte2<<8)|Temp_byte1;			// Combine the 2 bytes in to a 16-bit varibale 
	temp = (float) temp/16;									// Calculate the temperature 
	//delay_us(3000);												// delay for 3000 us for testinng purposes this line should be commented
	
	return temp;														// return the value (temperature in celcius)

}
