#ifndef STATE_H
#define STATE_H
#include "elev.h"
/**
  Elevator state for state machine.
*/
typedef enum tag_elevatorState {
	State_Idle = 		0,
	State_Move = 		1,
	State_DoorsOpen = 	2,
	State_Stop = 		3,
	State_Init = 		4,
} ElevState;


/**
  Elevator structure, contains memory of current state, requests and position.
*/
typedef struct tag_elevator {
	int 					currentFloor;
	elev_motor_direction_t 	currentDir;
	ElevState 				currentState;
	int 					queue[N_FLOORS][N_BUTTONS];  //2D array:   [index = Actual floor - 1] | order_up | order_down | cab_btn |

} Elevator;

#endif