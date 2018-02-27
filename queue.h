#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include "elev.h"

/**
 Initialize all element of the queue to false 
*/
void queue_init(bool queue[N_FLOORS][N_BUTTONS]);


/**
 Resets a 'bit' in the queue table.
 @param queue Pointer to the first element in the queue.
 @param floor, button Which button to set in the table.
*/
void queue_set(bool queue[N_FLOORS][N_BUTTONS], int floor, int button);


/**
 Resets an entire row of 'bits' in the queue table.
 @param queue The request queue.
 @param floor Which row to reset in the table.
 @param N_BUTTONS Number of rows to reset.
*/
void queue_reset(bool queue[N_FLOORS][N_BUTTONS], int floor);

/**
 Looks for new requests added by the user.
 @param queue The request queue.
 @return Returns true if something in the queue was updated.
*/
bool queue_update(bool queue[N_FLOORS][N_BUTTONS]);


/**
 Returns the next floor to move the elevator to.
 If elevator is moving up: checks for new orders to
 floors above the current floor.
 If elevator is moving down: checks for new orders to
 floors below the current floor.
 @return Floor number as integer between 0-3.
 @return -1 if there are no orders above/below the current floor.
*/
int queue_get_next_floor(bool queue[N_FLOORS][N_BUTTONS], int directon, int last_floor);


/**
 Checks whether the queue is empty or not.
 @return true if queue is empty, false if queue is not empty.
*/
bool queue_empty(bool queue[N_FLOORS][N_BUTTONS]);

/**
 Prints the queue.
*/
void queue_print(bool queue[N_FLOORS][N_BUTTONS]);

#endif
