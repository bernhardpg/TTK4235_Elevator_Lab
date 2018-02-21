#include "controller.h"
#include <stdio.h>
#include <stdbool.h>

#include "elev.h"
#include "io.h"
#include "channels.h"
#include "queue.h"

void controller() {

    initialize_hardware();

    // INITIALIZE ELEVATOR - LOOP
    while (1) {
	// Update last_floor
	last_floor = elev_get_last_floor(last_floor);

	// On a floor
	if (last_floor != -1) {
	    direction = DIRN_STOP;
	    elev_set_motor_direction(direction);
	    elev_set_door_open_lamp(1);
	    break;
	}
	
	// Set direction exactly once
	if (!direction) {
	    direction = DIRN_UP;
	    elev_set_motor_direction(direction);
	}
    }

    // Initialize 'global' program variables
    int last_floor = -1;
    int direction = DIRN_STOP; 
    int next_floor = -1;

    bool queue[N_FLOORS][N_BUTTONS];
    queue_init(queue);

    bool no_orders = true;
    bool door_open = false;

    // PROGRAM LOOP
    while (1) {
	
	// STOP HANDLER - Stop elevator and exit program if the stop button is pressed
	if (elev_get_stop_signal()) {
	    elev_set_motor_direction(DIRN_STOP);    
	    break;
	}

	// IDLE STATE - Do nothing while there are no orders
	if (no_orders) {
	    // Check for new orders
	    if (queue_update(queue)) {
		// Break out of idle state
		next_floor = queue_get_next_floor(queue, direction, last_floor, false);
		no_orders = false;
		// Close door
		elev_set_door_open_light(0);
	    }
	}

	// RUNNING STATE - Elevator is running
	else {
	    // Update last_floor
	    last_floor = elev_get_last_floor(last_floor);

	    // Look for new orders
	    if (queue_update(queue)) {
		// If there are any new orders, look for a closer one in the same direction.
		next_floor = queue_get_next_floor(queue, direction, last_floor, false);
		if (next_floor == -1) {
		    direction *= 1;
		    next_floor = queue_get_next_floor(queue, direction, last_floor, false);
		}
	    }

	    // When a destination is reached
	    if (next_floor == last_floor) {
		// Stop elevator temporary
		elev_set_motor_direction(DIRN_STOP);
		// Set door_open_light for 3 seconds
		light_and_door_handler(last_floor);

		// Clear out this floor from the queue
		queue_reset(queue, last_floor);

		// Check if queue now is empty
		if (queue_empty(queue)) {
		    // Go into IDLE STATE
		    elev_set_door_open_light(1);
		    no_orders = true;
		}
		else {
		    // Get new next_floor
		    next_floor = queue_get_next_floor(queue, direction, last_floor, false);
		    if (next_floor == -1) {
			direction *= -1;
			next_floor = queue_get_next_floor(queue, direction, last_floor, false);
		    }
		}
	    }
	    
	    // next_floor == -1 but the queue can't be empty
	    // Look for ALL orders
	    if (next_floor == -1) {
		next_floor = queue_get_next_floor(queue, direction, last_floor, true);
		if (next_floor == -1) {
			direction *= -1;
			next_floor = queue_get_next_floor(queue, direction, last_floor, true);
		}
	    }

	    // Start elevator if it has stopped
	    if (elev_not_moving) {
		elev_set_motor_direction(direction);
	    }
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


/**
 * Fix initiliaze for heis
 * fiks at man kalles queue_get_next_floor 7 ganger. Det går ikke
 *
 *
 *
 **/
