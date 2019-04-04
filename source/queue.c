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
	for (int i = 0; i < elev.currentFloor; i++) {		//check floors below current
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
	if (elev.currentDir == DIRN_UP) {
			return (if elev.queue[elev.currentFloor][0]);	//if orders in same direction(up)
	}
	else if (elev.currentDir == DIRN_DOWN) {
			return (if elev.queue[elev.currentFloor][1]);	//if orders in same direction(down)
	}
	/*
	ADD FUNCTIONALITY IF
		Hvis denne funksjonen er det som skal avgjøre om heisen skal gå til Idle! 
	*/
}

void q_add(int floor, elev_button_type_t button, Elevator* elev) {
	elev->queue[floor][button] = 1;						//add  order
	elev_set_button_lamp(button, floor, 1);			//set lamp
	
}

void q_complete(Elevator* elev) {
	int floor = elev->currentFloor;
	for (int i = 0; i < N_BUTTONS; i++) {
		elev->queue[floor][i] = 0;					//clear orders at current floor
		
		elev_set_button_lamp(i, elev->currentFloor, 0); 	//turn off lamp
	}	
}

void q_clear(Elevator* elev) {
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++) {
			elev->queue[i][j] = 0;						//clear queue
			
			elev_set_button_lamp(j, i, 0); 			//clear all order lamps : j = btn, i = floor
		}
	}
}
