#ifndef __QUEUE_H__
#define __QUEUE_H__

/**
 Struct to be used to contain the information from the different
 requests requested by the user.
*/
struct request {
    int floor, direction;
};


/**
 Returns next request to be handled from the queue.
*/
struct request queue_get_next_req(int elev_direction, struct request * queue);

/**
 Adds a new request to the queue.
 Returns a pointer to the first element in the new queue.
*/
struct request * queue_add_request(struct request new_request, struct request * queue);

/**
 Removes a request from the queue.
 Returns a pointer to the first element in the new queue.
*/
struct request * queue_remove_request(struct request old_request, struct request * queue);


#endif
