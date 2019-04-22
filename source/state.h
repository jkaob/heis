/**
* @file
* @brief State for the final state machine.
*/

#ifndef STATE_H
#define STATE_H
#include "elev.h"

/**
* Global variable. Emergency flag which is activated upon pressing the STOP button.
* If activated, last elevator direction will be saved in order to locate elevator between floors.
*/
extern int g_emergencyFlag;

/**
  Elevator state for state machine.
  @p Idle = 0, @p Move = 1, @p Doors_Open = 2, @p Stop = 3, @p Init = 4.
*/
typedef enum tag_elevatorState {
	State_Idle = 		0,
	State_Move = 		1,
	State_DoorsOpen = 	2,
	State_Stop = 		3,
	State_Init = 		4,
} ElevState;


/**
*  Elevator structure, contains memory of current state, position, direction and a 2-dimensional request array. 
*  Also contains direction before activating the stop button.
*  Request array contains Button type and Floor.
*  @brief Elevator structure, containing memory.
*/
typedef struct tag_elevator {
	int 					currentFloor;
	elev_motor_direction_t 	currentDir;
	int 					emergencyFloor;
	elev_motor_direction_t 	emergencyDir;
	ElevState 				currentState;
	int 					queue[N_FLOORS][N_BUTTONS]; 

} Elevator;

#endif