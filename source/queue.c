#include <stdio.h>
#include "queue.h"



bool q_check_orders_above(Elevator elev){
	if (elev.currentFloor == 3) return 0;
    for (int i = elev.currentFloor+1 ; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++) {
			
			if (elev.queue[i][j] == 1 ) 
				return 1; //orders above
		}
	}
	return 0; //no orders above
}

bool q_check_orders_below(Elevator elev) {
	if (elev.currentFloor == 0) return 0;
	for (int i = 0; i < elev.currentFloor ; i++) {	
		for (int j = 0; j < N_BUTTONS; j++) {
			if (elev.queue[i][j] == 1 ) 
				return 1;	//orders below
		}
	}
	return 0; //no orders below								
}



bool q_should_stop(Elevator elev) {
	//returns true, if ... 
		//If passenger wants to get off
	if (elev.queue[elev.currentFloor][2]) 
		return true;
	
	switch(elev.currentDir) {
		case DIRN_UP:
		//If orders in same direction(up)
			if (elev.queue[elev.currentFloor][0]) 
				return true;
		//If order in opposite direction(down) and no orders above
			if (elev.queue[elev.currentFloor][1] && !q_check_orders_above(elev)) 
				return true;	
			break;

		case DIRN_STOP:
		case DIRN_DOWN:
		//If orders in same direction(down)
			if (elev.queue[elev.currentFloor][1]) 
				return true;
		//If order in opposite direction(up) and no orders below 
			if (elev.queue[elev.currentFloor][0] && !q_check_orders_below(elev)) 
				return true; 
			break;
	}
		//If there are no other orders in the system
	if (!q_check_orders_below(elev) && !q_check_orders_above(elev)) 
		return true;
	
		//Else, return false
	return false;	
}

void q_add(int floor, elev_button_type_t button, Elevator* elev) {
	//Add request to queue-matrix
	elev->queue[floor][button] = 1;
	
	//Set lamp if lamp exists
	if (!((button == 1 && floor == 0) || (button == 0 && floor == 3)))
		elev_set_button_lamp(button, floor, 1);
	
}

void q_complete(Elevator* elev) {
	int f = elev->currentFloor;
	for (int b = 0; b < N_BUTTONS; b++) {
		
		//clear requests at current floor
		elev->queue[f][b] = 0;					
		
		//turn off lamp if lamp exists
		if (!((b == 1 && f == 0) || (b == 0 && f == 3)))
			elev_set_button_lamp(b, f, 0);
	}	
}

void q_clear(Elevator* elev) {
	for (int f = 0; f < N_FLOORS; f++) {
		for (int b = 0; b < N_BUTTONS; b++) {
			
			//clears the entire queue-matrix
			elev->queue[f][b] = 0;
			
			//disables all the requests lamps, if they exist
			if (!((b == 1 && f == 0) || (b == 0 && f == 3)))
				elev_set_button_lamp(b, f, 0); //
		}
	}
}



