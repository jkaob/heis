#pragma once 
#include <stdbool.h>
#include <stdio.h>
#include "elev.h"
#include "queue.h"

typedef enum tag_elevatorState {
	State_Idle = 0;
	State_Move = 1;
	State_DoorsOpen = 2;
	State_Stop = 3;
} ElevState;


typedef struct tag_elevator {
	int 					currentFloor;
	elev_motor_direction_t 	currentDir;	//enum from "elev.h"
	ElevState 				currentState;
	int 					queue[N_FLOORS][N_BUTTONS];  //2D array:   [index = Actual floor - 1] | order_up | order_down | cab_btn |

} Elevator;

void move(Elevator elev); //Enter STATE_Move

void open_doors(); //Enter STATE_DoorsOpen

elev_motor_direction_t set_direction(Elevator* elev);	//chooses (new) direction

bool is_at_floor(); //checks if at floor

void poll_buttons();