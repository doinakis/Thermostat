/*
Doinakis Michalis
e-mail: doinakis@ece.auth.gr
AEM : 9292
*/
#ifndef PROX_SENS_H
#define PROX_SENS_H

#include "dwt.h"
#include <gpio.h>
#include "delay.h"

#define echo PA_1									// Define the echo pin for the proximity sensor
#define trigger PA_4							// Define the trigger pin for the proximity sensor
#define threshold 30							// Define the threshold for which the movement will be recognised

// Initialization of the proximity sensor pins 
void prox_sens_init(void);

// Calculate distance using ultrasonic sensor 
float ultrasonic_dist(void);




#endif
