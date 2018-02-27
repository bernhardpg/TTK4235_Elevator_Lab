#include "controller.h"
#include <stdio.h>
#include <stdbool.h>

#include "elev.h"
#include "io.h"
#include "channels.h"
#include "queue.h"
#include "io_user.h"

void controller() {

    initialize_hardware();

    /**
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
    }*/

    // Initialize 'global' program variables
    int last_floor = -1;
    int direction = DIRN_STOP; 
    int next_floor = -1;

    bool queue[N_FLOORS][N_BUTTONS];
    queue_init(queue);

    bool no_orders = true;

    // PROGRAM LOOP
    while (1) {
	
	// STOP HANDLER - Stop elevator and exit program if the stop button is pressed
	// **********
	if (elev_get_stop_signal()) {
	    elev_set_motor_direction(DIRN_STOP);    
	    break;
	}

	// IDLE STATE - Do not move the elevator while there are no orders.
	// *********
	if (no_orders) {
	    
	    // Check for new orders for every iteration of the
	    // program loop while the program is in IDLE STATE.
	    // Break out of IDLE STATE once there are any orders.
	    if (queue_update(queue)) {
		next_floor = queue_get_next_floor(queue, direction, last_floor);
		no_orders = false;
	    }
	}

	// RUNNING STATE - Elevator is running
	// ***********
	else {
	    // Update last_floor for every iteration of the
	    // program loop while the program is in RUNNING STATE.
	    last_floor = elev_get_last_floor(last_floor);

	    // Look for new orders from users
	    // and update which order to exectute if the new order
	    // is better suited to the current direction and floor.
	    // (does not change directon or affect the engine)
	    if (queue_update(queue)) {
		next_floor = queue_get_next_floor(queue, direction, last_floor);
	    }

	    // Stop the elevator and open the doors for three
	    // seconds when a destination is reached,
	    // clear out the queue and go into IDLE STATE
	    // if the queue now is empty.
	    if (next_floor == last_floor) {
		elev_set_motor_direction(DIRN_STOP);
		door_and_lights_handler(last_floor);

		queue_reset(queue, last_floor);

		if (queue_empty(queue)) {
		    no_orders = true;
		}

		// Look for a new order to execute (with the current
		// motor direction), and start the engine if the queue
		// is not empty and if there exists such a new order.
		else {
		    next_floor = queue_get_next_floor(queue, direction, last_floor);
		    if (next_floor != -1) {
			elev_set_motor_direction(direction);
		    }
		}
	    }
	    
	    // Change direction, start engine and get new order if
	    // there are no more orders in the same direction as
	    // the elevator is currently moving.
	    if (next_floor == -1) {
		direction *= -1;
		elev_set_motor_direction(direction);
		next_floor = queue_get_next_floor(queue, direction, last_floor);
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
