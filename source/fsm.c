#include <stdio.h>
#include "fsm.h"

void move(Elevator* elev) {
	elev->currentState = State_Move;
	elev->currentDir = set_direction(elev);
	
}

void open_doors(Elevator* elev) {
	elev_set_motor_direction(0);			//stops elevator

	q_complete(elev)						//clears orders and turns off order lamps
	elev->currentState = State_DoorsOpen;	//changes state

	elev_set_door_open_lamp(1);
	timer_start(); 							//starts 3sec timer
}

elev_motor_direction_t set_direction(Elevator elev) {

	elev_motor_direction_t newDirection = DIRN_UP;
	switch(elev.currentDir) {
		case(DIRN_UP): 											//if current/last direction was UP
			if (check_orders_above(elev.currentFloor, elev.queue))  {
				newDirection = DIRN_UP;
				//elev->currentDir = DIRN_UP;
			}
			else if (check_orders_below(elev.currentFloor, elev.queue)) {
				newDirection = DIRN_DOWN;
				//elev->currentDir = DIRN_DOWN;
			}
			break;
	
		case(DIRN_DOWN): 										//if current/last direction was DOWN

		case(DIRN_STOP):										//if last direction was STOP. Same as down. Doesnt matter.
			if (check_orders_below(elev.currentFloor, elev.queue)) {
				newDirection = DIRN_DOWN;
				//elev->currentDir = DIRN_DOWN;
			}
			else if (check_orders_above(elev.currentFloor, elev.queue))  {
				newDirection = DIRN_UP;
				//elev->currentDir = DIRN_UP;
			}
			break;

		default: break;
	}
	return newDirection;
}

bool is_at_floor() {
	return if(elev_get_floor_sensor_signal() == -1);
}