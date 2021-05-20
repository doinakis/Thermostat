/*
Doinakis Michalis
e-mail: doinakis@ece.auth.gr
AEM : 9292
*/
#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <platform.h>
#include <gpio.h>
#include <delay.h>
#include <timer.h>
#include <queue.h>
#include <stdio.h>
#include "lcd.h"
#include "dwt.h"
#include "prox_sens.h"
#include "temp_sens.h"

#define Screen PA_5												// Define the A pin of the display in order to turn the backlight on/off
#define Fan_Pin PB_6											// Define the pin that is connected to the fan (green Led)
#define Low_Temp_Pin PA_6									// Define the pin of the blue Led to indicate low temperature
#define High_Temp_Pin PA_7								// Define the pin of the red Led to indicare high temperature 

/*
	Variables explained in main.c file 
*/
extern volatile int lcd_active_count;	
extern volatile int temp_ready_flag;	
extern volatile int lcd_active_count;
extern volatile int temp_count;
extern volatile int get_temp_flag;
extern volatile int lcd_flag;

/**********************************************
	Timer interrupt handler 
*/
void timer_handler(void);
void thermostat_init(void);



#endif
