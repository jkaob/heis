#ifndef STATE_H
#define STATE_H
#include "elev.h"

/**
Emergency flag which is activated upon pressing the STOP button.
If activated, last elevator direction will be saved in order to locate elevator between floors.
*/
extern int g_emergencyFlag;

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
  Elevator structure, contains memory of current state, position, direction and a 2-dimensional request array. 
  Also contains direction before activating the stop button.
  @brief Elevator structure, containing memory.
*/
typedef struct tag_elevator {
	int 					currentFloor;
	elev_motor_direction_t 	currentDir;
	int 					emergencyFloor;
	elev_motor_direction_t 	emergencyDir;
	ElevState 				currentState;
	int 					queue[N_FLOORS][N_BUTTONS];  //2D array:   [index = Actual floor - 1] | order_up | order_down | cab_btn |

} Elevator;

#endif