// Implementation of the order queue.
// 2018, Theodor Husefest and Bernhard Paus Græsdal.

#include "queue.h"
#include <stdbool.h>
#include <stdio.h>

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
    // Check every available button for user input.
    // Interpretation of i and j:
    // i: Floor
    // j: Button type. 0 - UP, 1 - DOWN, 2 - COMMAND.
    for (int i = 0; i < N_FLOORS; i++) {
	for (int j = 0; j < N_BUTTONS; j++) {

	    if (!((j == 1) && (i == 0))
		    && !((j == 0) && (i == 3))
		    && (elev_get_button_signal(j, i))) {

		if (!queue[i][j]) {
		    queue_set(queue, i, j);
		    return true;
		}
	    }
	}
    }

    return false;
}


int queue_get_next_floor(bool queue[N_FLOORS][N_BUTTONS],
		int direction, int last_floor) {

    // Interpretation of collumn numbers:
    // 0 - UP
    // 1 - DOWN
    // 2 - COMMAND

    // Find the most efficient order to execute based on
    // the current direction and last_floor.
    switch (direction) {
	case DIRN_UP:
	    // Check for orders to move the elevator up 
	    // and orders from the command console.
	    for (int i = last_floor + 1; i < N_FLOORS; i++) {
		if ((queue[i][2]) || (queue[i][0])) {
		    return i;
		}
	    }
	    // Check for orders to go down if there are
	    // no more up orders from up or command buttons.
	    // If there exists orders to go down
	    // return the floor of this new order.
	    for (int i = N_FLOORS - 1; i > last_floor - 1; i--) {
		if (queue[i][1] || queue[i][2]) {
		    return i;
		}
	    }
	    break;
	
	case DIRN_DOWN:
	    // Check for orders to move the elevator down 
	    // and orders from the command console.
	    for (int i = last_floor - 1; i >= 0; i--) {
		if ((queue[i][2]) || (queue[i][1])) {
		    return i;
		}
	    }
	    // Check for orders to go up if there are
	    // no more down orders from down or command buttons.
	    // If there exists orders to go up
	    // return the floor of this new order.
	    for (int i = 0; i < last_floor + 1; i++) {
		if (queue[i][0] || queue[i][2]) {
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


void queue_print(bool queue[N_FLOORS][N_BUTTONS]) {
    for (int i = 0; i < N_FLOORS; i++) {
	for (int j = 0; j < N_BUTTONS; j++) {
	    printf("%d", queue[i][j]);
	    printf(" ");
	}	
	printf("\n");
    }
    printf("\n\n*****\n\n");
}

void queue_clear(bool queue[N_FLOORS][N_BUTTONS]) {
    for (int i = 0; i < N_FLOORS; i++) {
	for (int j = 0; j < N_BUTTONS; j++) {
	    queue[i][j] = 0;
	}
    }
}

