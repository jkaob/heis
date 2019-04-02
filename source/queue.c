#include <stdio.h>
#include "queue.h"

for (int i = 0; i < N_FLOORS; i++) {
	for int i = 0; i < N_BUTTONS; i++) {
		queue[i][j] = 0;						//init queue
	}
}


bool check_orders_above(int currentFloor, int** queue){
	
	if (currentFloor == 3) return 0;
    for (int i = currentFloor; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++) {
			
			if ( queue[i][j] == 1 ) return 1;		//orders above
		}
	}
	return 0;	//no orders above
}

bool check_orders_below(int currentFloor, int** queue) {
	
	if (currentFloor == 0) return 0;
	for (int i = currentFloor-1 ; i-- >= 0; ) {		//floors below current
		for (int j = 0; j < N_BUTTONS; j++) {
			if ( queue[i][j] == 1 ) return 1;		//orders below
		}
	}
	return 0;	//no orders below
}

void q_add(int floor, elev_button_type_t button, int** queue) {
	queue[floor][button] = 1;				//add  order
	elev_set_button_lamp(button, floor, 1;	//set lamp
	
}

void q_complete(int currentFloor, int** queue) {
	for (int i = 0; i < N_BUTTONS; i++) {
		queue[currentFloor][i] = 0;					//clear orders at current floor
		elev_set_button_lamp(i, currentFloor, 0); 	//turn off lamp
	}	
}

void q_clear(int** queue) {
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++) {
			queue[i][j] = 0;
			elev_set_button_lamp(j, i, 0); //clear all lights : j = btn, i = floor
		}
	}
}
