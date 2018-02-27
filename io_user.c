// INPUT OUTPUT file for user interfaces. This includes buttun_handler, get_last_floor and 
// stop_handler, 

#include "io_user.h"
#include "elev.h"
#include "channels.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void door_and_lights_handler(int current_floor){
   
    elev_set_floor_indicator(current_floor); 
    // Shuts of all the lights on current floor (all orders on
    // current floor completed)
    int i = current_floor;
    for (int j = 0; j < 3; j++) {
	if (!((i == 0) && (j == 1))
		&& !((i == 3) && (j == 0))) {
	    elev_set_button_lamp(j, i, 0);
	}
    }

     //Opens the door for 3 seconds
    elev_set_door_open_lamp(1); 
    delay(3000);  
    elev_set_door_open_lamp(0); 
    

   
}

void set_ordered_lights(bool queue[N_FLOORS][N_BUTTONS]) {
    // Set lights based on the queue (function is only called when
    // queue is updated)
    for (int i = 0; i < N_FLOORS; i++)	{
	for (int j = 0; j < N_BUTTONS; j++) {
	    if ((queue[i][j] == true)
		    && !((i == 0) && (j == 1))
		    && !((i == 3) && (j == 0))) {
		elev_set_button_lamp(j,i,1);
	    }
	}
    } 
}



void delay(int ms) {
    int time = 1000 * ms;

    clock_t start_time = clock();

    while (clock() < start_time + time);
}

