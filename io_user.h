#ifndef __IO_USER_H__
#define __IO_USER_H__

/**
Returns the current/last floor
*/ 
int elev_get_last_floor(int last_floor);


/** 
Stop_handler is the function that opens the door, turns off
lights at current floor and removes from queue. WILL TAKE 3 SECONDS
*/

void door_and_lights_handler(bool** queue, int current_floor); 

/**
Set_lights takes in the queue and set lights
*/

void set_lights(bool** queue);

#endif
