// 

#ifndef __IO_USER_H__
#define __IO_USER_H__

#include <stdbool.h>
#include "elev.h"


/** 
 Changes floor indicator and turns off all lights on current floor
 @param current_floor current floor of the elevator
*/

void io_user_clear_lights_order_completed(int current_floor); 

/**
 Turns on all lights based on queue
 Uses whole queue since many buttons can be pushed simultaneously
 @param queue   
*/

void io_user_set_ordered_lights(bool queue[N_FLOORS][N_BUTTONS]);


#endif


