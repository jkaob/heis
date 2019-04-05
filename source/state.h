#ifndef STATE_H
#define STATE_H
#include "elev.h"

typedef enum tag_elevatorState {
	State_Idle = 0,
	State_Move = 1,
	State_DoorsOpen = 2,
	State_Stop = 3,
} ElevState;


typedef struct tag_elevator {
	int 					currentFloor;
	elev_motor_direction_t 	currentDir;	//enum from "elev.h"
	ElevState 				currentState;
	int 					queue[N_FLOORS][N_BUTTONS];  //2D array:   [index = Actual floor - 1] | order_up | order_down | cab_btn |

} Elevator;

#endif