#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


struct request {
    int floor;
    int direction;
};

void controller();
int initialize_hardware();
bool request_handler(int current_request.floor, int last_floor);


#endif
