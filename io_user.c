// INPUT OUTPUT file for user interfaces. This includes buttun_handler, get_last_floor and 
// stop_handler, 

#include "io_user.h"
#include "elev.h"
#include "channels.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int elev_get_last_floor(int last_floor) {
    // Gets last floor

    int floor_sensor_signal = elev_get_floor_sensor_signal();

    if ((floor_sensor_signal != last_floor)
	    && (floor_sensor_signal > -1)) {

				return floor_sensor_signal;
    }
    
    return last_floor;
}



void door_and_lights_handler(int current_floor){
		//Opens the door for 3 seconds
		elev_set_door_open_lamp(1); 
		delay(3000);  
		elev_set_door_open_lamp(0); 

		// Shuts of all the lights on current floor (all orders on current floor completed)
		for (int i = 0; i < 3; i++) {
				elev_set_button_lamp(i, current_floor, 0);
		}
}

void set_light(bool** queue) {
		// Set lights based on the queue (function is only called when
		// queue is updated)
		for (int i = 0; i < 3; i++)	{
				for (int j = 0; j < 3; j++) {
						if (queue[i][j] == true && elev_get_button_lamp(j,i) == 0) {
								elev_set_button_lamp(j,i,1);
						}
				}
		} 
}



void delay(int ms) {
		clock_t start = clock();
		while ((clock-start) * 1000 / CLOCKS_PER_SEC < ms); 
}


