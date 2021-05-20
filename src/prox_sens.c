/*
Doinakis Michalis
e-mail: doinakis@ece.auth.gr
AEM : 9292
*/
#include "prox_sens.h"


/*
	Initialize the trigger and the echo pin as output and input respectively
*/

void prox_sens_init(void){
	
	gpio_set_mode(trigger,Output);
	gpio_set_mode(echo,Input);
	
}

float ultrasonic_dist(void){
	
	float debounce_time = 0;																									// Time it took the ultrasonic wave to come back 
	float distance = 0;																												// Initialization of the return value (distance)
	KIN1_InitCycleCounter();																									// Initialization of dwt counter 
	KIN1_ResetCycleCounter();																									// Reset the cycle counter 
	gpio_set(trigger,Reset);																									// Reset the trigger pin : set it to 0
	delay_us(2);																															// Delay for 2 us 
	gpio_toggle(trigger);																											// Toggle the trigger pin : set it to high state since the previous one was low = 0 
	delay_us(10);																															// Delay for 10 us 
	gpio_set(trigger,Reset);																									// Reset the trigger pin : set it to 0
	
	// Wait until the echo pin gets high 
	while(!(gpio_get(echo))); 
	KIN1_EnableCycleCounter();																								// Enable dwt hardware 
	KIN1_ResetCycleCounter();																									// Reset the counter again 
	
	// Wait until the ultrasonic signal comes back after bouncing to surface (echo pin stops being high)
	while(gpio_get(echo)); 
	debounce_time = (float) KIN1_GetCycleCounter()/SystemCoreClock;						// Divide the cycle counter from dwt with the SystemCoreClock to calculate the time in seconds
	
	/* 
	distance = time * velocity (sound velocity = 343 m/s at 25 celcius) divided by 2 cause we measured the time for the signal till it hit the surface and come back
		multiplied with 100 to calculate the distance in centimeters 
	*/
	distance  = debounce_time * 34300/2; 
	KIN1_DisableCycleCounter();																								// Disable dwt hardware
	return distance;																													// Return the distance calculated

}
