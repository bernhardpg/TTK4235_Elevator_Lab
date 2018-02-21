// INPUT OUTPUT file for user interfaces. This includes buttun_handler, get_last_floor and 
// stop_handler

#include "io_user.h"
#include "elev.h"
#include "queue.h"

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



void stop_handler(){
		elev_set_door_open_lamp(1); 
		delay(3000);
		elev_set_door_open_lamp(0); 

}


void delay(int ms) {
		clock_t start = clock();
		while ((clock-start) * 1000 / CLOCKS_PER_SEC < ms); 
}


