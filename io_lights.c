// Input and output functions to handle the elevator lights.
// 2018, Theodor Husefest and Bernhard Paus Græsdal.

#include "io_lights.h"
#include "elev.h"
#include "channels.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void io_user_clear_lights_on_floor(int current_floor){
   
    //Change floor indicator to current floor.
    elev_set_floor_indicator(current_floor); 

    // Turn off all the lights on current floor.
    int i = current_floor;
    for (int j = 0; j < 3; j++) {
	if (!((i == 0) && (j == 1))
		&& !((i == 3) && (j == 0))) {
	    elev_set_button_lamp(j, i, 0);
	}
    }
   
}

void io_user_set_ordered_lights(bool queue[N_FLOORS][N_BUTTONS]) {
    // Set lights based on the queue (function is only called when
    // queue is updated).
	
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




