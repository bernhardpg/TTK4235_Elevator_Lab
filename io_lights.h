// Input and output functions to handle the elevator lights.
// 2018, Theodor Husefest and Bernhard Paus Græsdal.

#ifndef __IO_LIGHTS_H__
#define __IO_LIGHTS_H__

#include <stdbool.h>
#include "elev.h"


/** 
 Changes floor indicator and turns off all lights on current floor
 @param current_floor current floor of the elevator
*/

void io_lights_clear_lights_on_floor(int current_floor); 

/**
 Turns on all lights based on queue
 Uses whole queue since many buttons can be pushed simultaneously
 @param queue   
*/

void io_lights_set_ordered_lights(bool queue[N_FLOORS][N_BUTTONS]);


#endif


