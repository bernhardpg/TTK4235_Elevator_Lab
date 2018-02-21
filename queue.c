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
	    }
	}
    }
}


int queue_get_next_floor(bool queue[N_FLOORS][N_BUTTONS],
		int direction, int last_floor) {
    
    int button_row;
    // Find the closest request in the same direction
    // or without direction (from cmd buttons)
    switch (direction) {
	    case DIRN_UP:
		button_row = 0;
		for (int i = last_floor; i < N_FLOORS; i++) {
		    if ((queue[i][button_row])
			    || (queue[i][1])) {
			return i;
		    }
		}
		break;

	    case DIRN_DOWN:
		button_row = 2;
		for (int i = last_floor; i > 0; i--) {
		    if ((queue[i][button_row])
			    || (queue[i][1])) {
			return i;
		    }
		}
		break;
    }

    // No more requests in the same direction
    // or from the cmd buttons.
    return -1;
}
