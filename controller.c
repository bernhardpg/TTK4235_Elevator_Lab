#include "controller.h"
#include <stdio.h>
#include "elev.h"
#include "io.h"
#include "channels.h"



void controller() {
    
    initialize_hardware();
 
    // Initialize 'global' program variables
    int last_floor = -1;
    struct request current_req;
    
    struct request queue[];

    // PROGRAM LOOP
    while (1) {

	// Change direction when we reach top/bottom floor
	if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
	    elev_set_motor_direction(DIRN_DOWN);
	} else if (elev_get_floor_sensor_signal() == 0) {
	    elev_set_motor_direction(DIRN_UP);
	}

	// Stop elevator and exit program if the stop button is pressed
	if (elev_get_stop_signal()) {
	    elev_set_motor_direction(DIRN_STOP);
	    break;
	}

	last_floor = elev_get_last_floor(last_floor);
	//printf("last_floor: %d \n", last_floor);
	
	if (request_handler(current_request)) {
	    handle_new_request(queue_get_next());
	}
}

int initialize_hardware() {
    // Initialize hardware
    
    if (!elev_init()) {
	printf("Unable to initialize elevator hardware!\n");
	return 1;
    }

    elev_set_motor_direction(DIRN_STOP);

    printf("Press STOP button to stop elevator and exit program.\n");
    return 0;
}

void move_to_floor(int floor) {

} 

