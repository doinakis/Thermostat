/*
Doinakis Michalis
e-mail: doinakis@ece.auth.gr
AEM : 9292
*/
#ifndef TEMP_SENS_
#define TEMP_SENS_H

#include <delay.h>
#include <gpio.h>
#include <platform.h>

#define Temp_Pin PC_0
#define Low_Temp 15
#define High_Temp 29

#define SKIP_ROM 0xCC
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xBE


/**********************************************************************
	Initialization of the sensor, following the steps mentioned 
	in the datasheet.
	Return value : 1 sensor is connected 
								-1 sensor is not connected
*/
uint8_t start_temp_sens(void);

/**********************************************************************
	Writes 8-bit data to the sensor
*/

void write_temp_sens(uint8_t data);

/**********************************************************************
	Reading 8-bit data from the sensor
*/

uint8_t read_temp_sens(void);

/**********************************************************************
	Uses all the previous declered functions to read the temperature 
	from the sensor 
*/

float read_temp(void);

#endif
