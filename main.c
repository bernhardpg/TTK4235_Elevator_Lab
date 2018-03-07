// Implementation of elevator project.
// 2018, Theodor Husefest and Bernhard Paus Græsdal.


#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "elev.h"
#include "io.h"
#include "channels.h"
#include "queue.h"
#include "io_lights.h"

int main () {

    // Initialize 'global' program variables

    int current_floor = -1;		// Sensor floor signal. Will be -1 if elevator is inbetween floors.
    int last_floor = -1;		// Keeps track of the last known floor.
    int next_floor = -1;		// Working variable used to hold the calculated next floor.	
    int direction = DIRN_UP;		// Working variable used to know which direction in the queue to look for new orders.

    clock_t start_time;			// Variable to keep track off the doors.
    int time_delay = 3*1000000;		// How long the elev will stop (in this case 3 seconds).

    bool queue[N_FLOORS][N_BUTTONS];	// Two dimensional matrix corresponding to all available elevator buttons.
    queue_init(queue);

    bool no_orders = true;		// Variable to keep track of wheter the queue is empty or not.

    elev_initialize_hardware(direction);

    // INITIALIZE LOOP
    while (1) {
	
	// Move the elevator to a floor if necessary.
	last_floor = elev_get_last_floor(last_floor);
	if (last_floor != -1) {
	    elev_set_motor_direction(DIRN_STOP);
	    printf("CHANGING TO IDLE STATE\n");
	    break;
	}
    }

    // PROGRAM LOOP
    while (1) {

	// STOP STATE - Stops elevator, clears queue, turns off all lights 
	// and opens door if the elevator is currently on a floor.
	// **********
	if (elev_get_stop_signal()) {
	    elev_set_stop_lamp(1);

	    // Make the elevator able to go back to previous floor if
	    // the elevator is stopped in between floors.
	    if (next_floor == last_floor) {
		direction *= -1;
	    }

	    // Reset the queue and which floor to go to next.
	    if (!no_orders) {
		elev_stop_button_handler(current_floor);
		queue_init(queue);
		next_floor = -1;
		no_orders = true;
	    }

	    else if (current_floor != -1) {
		elev_set_door_open_lamp(1);	
	    }

	    elev_set_stop_lamp(0);
	}	
	
		
	// IDLE STATE - Do not move the elevator while there are no orders.
	// *********
	else if (no_orders) {


	    // Check for new orders for every iteration while the
	    // program is in IDLE STATE.
	    // Break out of IDLE STATE once there are any orders,
	    // and calculate new next floor and which direction to
	    // move the elevator to.

	    if (queue_update(queue)) {
	
		io_user_set_ordered_lights(queue);
		elev_set_door_open_lamp(0);

		next_floor = queue_get_next_floor(queue, direction, last_floor);

		if (next_floor == last_floor) {
		    direction *= -1;
		} 

		direction = elev_set_direction(direction, next_floor, last_floor);	
		no_orders = false;
	    }
	}

	// RUNNING STATE - Elevator is running
	// ***********
	else {

	    direction = elev_set_direction(direction, next_floor, last_floor);
	    current_floor = elev_get_floor_sensor_signal();

	    elev_set_floor_indicator(last_floor);

	    last_floor = elev_get_last_floor(last_floor);
	

	    // Look for new orders from users
	    // and calculate whether it's more efficient to execute
	    // the new order 'on the way' (does not change directon
	    // or affect the engine).
	    if (queue_update(queue)) {
		io_user_set_ordered_lights(queue);
		next_floor = queue_get_next_floor(queue, direction, last_floor);
	    }

	    // Stop the elevator and open the doors for a given
	    // amount of  time when a destination is reached,
	    // remove finished order from queue and check
	    // whether to enter IDLE STATE. 
	    if ((next_floor == last_floor)
		    && (next_floor == current_floor)) {
			
		elev_set_motor_direction(DIRN_STOP);
		io_user_clear_lights_on_floor(last_floor);			
		
		elev_set_door_open_lamp(1);
		start_time = clock();

		while (clock() < start_time + time_delay) {
		    if (queue_update(queue)) {
			io_user_set_ordered_lights(queue);
			io_user_clear_lights_on_floor(last_floor);			
		    }
		}

		elev_set_door_open_lamp(0);
		queue_reset(queue, last_floor);

		// Check whether the queue is now empty or not. If not,
		// look for a new order to execute, based on the current direction
		// and last floor. Set the direction if a new order is found.
		if (queue_empty(queue)) {
		    no_orders = true;
		}

		else {
		    next_floor = queue_get_next_floor(queue, direction, last_floor);

		    if (next_floor != -1) {
			direction = elev_set_direction(direction, next_floor, last_floor);	
		    }
		}
	    }
	    
	    // If no new order is found at the end of an iteration, change direction
	    // to look for a new order and calculate which order to execute next.
	    if (next_floor == -1) {
		direction *= -1;
		next_floor = queue_get_next_floor(queue, direction, last_floor);
		direction = elev_set_direction(direction, next_floor, last_floor);
	    }
	}
    }

    return 0;
}
