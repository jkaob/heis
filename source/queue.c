#include <stdio.h>
#include "queue.h"



bool check_orders_above(Elevator elev){
	if (elev.currentFloor == 3) return 0;
    for (int i = elev.currentFloor+1 ; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++) {
			
			if (elev.queue[i][j] == 1 ) return 1;		//orders above
		}
	}
	return 0;										//no orders above
}

bool check_orders_below(Elevator elev) {
	if (elev.currentFloor == 0) return 0;
	for (int i = 0; i < elev.currentFloor ; i++) {		//check floors below current
		for (int j = 0; j < N_BUTTONS; j++) {
			if (elev.queue[i][j] == 1 ) return 1;		//orders below
		}
	}
	return 0;										//no orders below
}



bool should_stop(Elevator elev) { 														//also add if there are no orders above/below?
	if (elev.queue[elev.currentFloor][2]) {		//If passenger wants to get off
			return true;
	}
	switch(elev.currentDir) {
		case DIRN_UP:
			if (elev.queue[elev.currentFloor][0]) return true; //if orders in same direction(up)
			if (elev.queue[elev.currentFloor][1] && !check_orders_above(elev)) return true;	//if order in opposite direction(down) and no orders above
			break;

		case DIRN_STOP:
		case DIRN_DOWN:
			if (elev.queue[elev.currentFloor][1]) return true; //if orders in same direction(down)
			if (elev.queue[elev.currentFloor][0] && !check_orders_below(elev)) return true; //if order in opposite direction(up) and no orders below
			break;
	}
	return false;
	//else if (!check_orders_above(elev) && !check_orders_below(elev)) {
	//	return true;
	//}
	
}

void q_add(int floor, elev_button_type_t button, Elevator* elev) {
	elev->queue[floor][button] = 1;					//add  order
	elev_set_button_lamp(button, floor, 1);			//set lamp
	
}

void q_complete(Elevator* elev) {
	int floor = elev->currentFloor;
	for (int i = 0; i < N_BUTTONS; i++) {
		elev->queue[floor][i] = 0;					//clear orders at current floor
		
		if (!((i == 1 && floor == 0) || (i == 0 && floor == 3))) {
			elev_set_button_lamp(i, floor, 0); 	//turn off lamp
		}
	}	
}

void q_clear(Elevator* elev) {
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++) {
			elev->queue[i][j] = 0;						//clear queue
			
			if (!((j == 1 && i == 0) || (j == 0 && i == 3))) { //checks if lamp exists
			elev_set_button_lamp(j, i, 0); 			//clear all order lamps : j = btn, i = floor
			}
		}
	}
}
