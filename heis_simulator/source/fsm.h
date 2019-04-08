#include <stdio.h>
#include "elev.h"

typedef enum {
	State_Idle = 0;
	State_Move = 1;
	State_DoorOpen = 2;
	State_Stop = 3;
} ElevState


typedef struct {
	int 					currentFloor;
	elev_motor_direction_t 	currentDir;	//enum from "elev.h"
	ElevState 				currentState;
} Elevator


void open_doors();

bool should_stop(int currentFloor, int**queue);		//checks queue and decides if to stop at new floor

void stop(); //denne er jo veldig overflødig

void poll_buttons();