#include "fsm.h"

void open_doors(Elevator* elev) {
	elev->currentState = State_DoorsOpen;
	
	elev_set_motor_direction(0);
	elev_set_door_open_lamp(1);
	
	timer_start(); //må defineres
}

elev_motor_direction_t set_direction(Elevator* elev, int currentFloor, int** queue) {
	elev_motor_direction_t newDirection;
	
	switch(elev->currentDir)
		case(DIRN_UP): 											//if current/last direction was UP
			if (check_orders_above(elev->currentFloor, queue))  {
				newDirection = DIRN_UP;
				elev->currentDir = DIRN_UP;
			}
			else if (check_orders_below(elev->currentFloor, queue)) {
				newDirection = DIRN_DOWN;
				elev->currentDir = DIRN_DOWN;
			}
			break;
			
		case(DIRN_DOWN): 										//if current/last direction was DOWN
			
		case(DIRN_STOP):										//if last direction was STOP. Same as down. Doesnt matter.
			if (check_orders_below(elev->currentFloor, queue)) {
				newDirection = DIRN_DOWN;
				elev->currentDir = DIRN_DOWN;
			}
			else if (check_orders_above(elev->currentFloor, queue))  {
				newDirection = DIRN_UP;
				elev->currentDir = DIRN_UP;
			}
			break;
			
		default: break;
	}
	return newDirection;
}