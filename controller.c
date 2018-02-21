#include "controller.h"
#include <stdio.h>
#include <stdbool.h>

#include "elev.h"
#include "io.h"
#include "channels.h"
#include "queue.h"



void controller() {
    
    initialize_hardware();
 
    // Initialize 'global' program variables
    int last_floor = -1;
    int current_floor = -1;
    int direction = 0;
    int next_floor = 0;

    // PROGRAM LOOP
    while (1) {
	/*
	 * // Change direction when we reach top/bottom floor
	if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
	    elev_set_motor_direction(DIRN_DOWN);
	} else if (elev_get_floor_sensor_signal() == 0) {
	    elev_set_motor_direction(DIRN_UP);
	}*/

	// Stop elevator and exit program if the stop button is pressed
	if (elev_get_stop_signal()) {
	    elev_set_motor_direction(DIRN_STOP);
	    break;
	}

    }
}

int initialize_hardware() {
    // Initialize hardware
    
    if (!elev_init()) {
	printf("Unable to initialize elevator hardware!\n");
	return 1;
    }

    elev_set_motor_direction(DIRN_STOP);
    // Set a start direction.
    // TO BE REPLACED

    printf("Press STOP button to stop elevator and exit program.\n");
    return 0;
}
