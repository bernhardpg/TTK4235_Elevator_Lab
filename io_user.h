#ifndef __IO_USER_H__
#define __IO_USER_H__

/**
Returns the current/last floor
*/ 
int elev_get_last_floor(int last_floor);


/** 
Stop_handler is the function that opens the door, turns off
lights and removes from queue. WILL TAKE 3 SECONDS
*/

void stop_handler(bool** queue, int current_floor); 

