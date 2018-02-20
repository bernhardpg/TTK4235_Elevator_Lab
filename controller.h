#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


struct request {
    int floor;
    int direction;
};

void controller();

int initialize_hardware();


#endif
