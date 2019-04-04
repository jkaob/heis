#include <stdio.h>
#include "elev.h"
#include "queue.h"

typedef enum {
	State_Idle = 0;
	State_Move = 1;
	State_DoorsOpen = 2;
	State_Stop = 3;
} ElevState


typedef struct {
	int 					currentFloor;
	elev_motor_direction_t 	currentDir;	//enum from "elev.h"
	ElevState 				currentState;
} Elevator

void move(elev Elev); //Enter STATE_Move

void open_doors(); //Enter STATE_DoorsOpen

bool should_stop(int currentFloor, int**queue);		//checks queue and decides if to stop at new floor

void poll_buttons();