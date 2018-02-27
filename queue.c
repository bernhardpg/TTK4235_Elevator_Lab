#include "queue.h"
#include <stdbool.h>

#include "elev.h"

void queue_init(bool queue[N_FLOORS][N_BUTTONS]) {
    for (int i = 0; i < N_FLOORS; i++) {
	for (int j = 0; j < N_BUTTONS; j++) {
	    queue[i][j] = 0;
	}
    }
}


void queue_set(bool queue[N_FLOORS][N_BUTTONS], int floor, int button) {
    queue[floor][button] = true;
}


void queue_reset(bool queue[N_FLOORS][N_BUTTONS], int floor) {
    for (int i = 0; i < N_BUTTONS; i++) {
	queue[floor][i] = false;
    }
}


bool queue_update(bool queue[N_FLOORS][N_BUTTONS]) {
    for (int i = 0; i < N_FLOORS; i++) {
	for (int j = 0; j < N_BUTTONS; j++) {
	    if (elev_get_button_signal(j, i)) {
		queue_set(queue, i, j);
		return true;
	    }
	}
    }
    return false;
}


int queue_get_next_floor(bool queue[N_FLOORS][N_BUTTONS],
		int direction, int last_floor) {
    
    // - If the elevator is moving up:
    // check for orders from floors above the current floor,
    // and return the order which is closest to the current floor.
    // - If the elevator is moving down:
    // check for orders from floors below the current floor,
    // and return the order which is closest to the current floor.

    // Interpretation of collumn numbers:
	// 0 - UP
	// 1 - DOWN
	// 2 - COMMAND

    switch (direction) {
	    case DIRN_UP:
		// Check for orders to move the elevator down
		// and orders from the command console.
		for (int i = last_floor; i < N_FLOORS; i++) {
		    if (queue[i][0]) {
			return i;
		    }
		    if ((queue[i][2])
			    || (queue[i][1])) {
			return i;
		    }
		}
		// Check for orders to go down if there are
		// no more orders to go down or from the
		// command console.
		// orders in the opposite direction
		for (int i = last_floor; i < N_FLOORS; i++) {
		    if (queue[i][1]) {
			return i;
		    }
		}
		
		break;
	    
	    case DIRN_DOWN:
		// Check for orders to move the elevator down 
		// and orders from the command console.
		for (int i = last_floor; i > 0; i--) {
		    if (queue[i][1]) {
			return i;
		    }
		    if ((queue[i][2])
			    || (queue[i][1])) {
			return i;
		    }
		}
		// Check for orders to go up if there are
		// no more orders to go down or from the
		// command console.
		for (int i = last_floor; i > 0; i--) {
		    if (queue[i][0]) {
			  return i;
		    }
		}
		break;
    }

    // Return -1 if there are no orders above/below
    // (depending on the direction) the current floor.
    return -1;
}


bool queue_empty(bool queue[N_FLOORS][N_BUTTONS]) {
    for (int i = 0; i < N_FLOORS; i++) {
	for (int j = 0; j < N_BUTTONS; j++) {
	    if (queue[i][j]) {
		return false;	    
	    }
	}
    }
    return true;
}
