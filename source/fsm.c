#include <stdio.h>
#include "fsm.h"

int fsm_main_loop(Elevator* elev) {
	while(1) {
	
		{ //IF STOP BUTTON IS PRESSED
			if (elev_get_stop_signal()) {
				fsm_stop_btn_pressed(elev);
			}
		}
	
		{ //IF REQUEST BUTTON IS PRESSED 
			elev_button_type_t button;
			int floor;
			if (is_btn_pressed(&button, &floor)) { 
				fsm_request_btn_pressed(elev, floor, button);
			}
		}
	
		{	//IF ARRIVAL AT FLOOR
			if (elev_get_floor_sensor_signal() != -1) {
				fsm_arrive_at_floor(elev, elev_get_floor_sensor_signal());
			}
		}
	
		{	//IF TIMER TIMEOUT
			if (timer_check() && g_timerFlag == 1) {
				fsm_timer_timeout(elev);
			}
		}
	}
	return 0;
}

int fsm_init_elevator(Elevator* elev) {
	elev->currentState = State_Init;
	g_timerFlag = 0;
	elev_set_motor_direction(DIRN_DOWN);

	while(elev_get_floor_sensor_signal() == -1) {		//Kjører ned til nærmeste etasje
	}
	elev_set_motor_direction(DIRN_STOP);

	elev->currentDir = DIRN_DOWN;
	elev->currentFloor = elev_get_floor_sensor_signal();
	elev_set_floor_indicator(elev_get_floor_sensor_signal());
	
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++) {
			elev->queue[i][j] = 0;
		}
	}
	elev->currentState = State_Idle;
	return 1;
}



void fsm_arrive_at_floor(Elevator* elev, int floor){
	elev_set_floor_indicator(floor);		
	if (elev->currentFloor == floor) return; 	//hvis sensoren allerede har vært aktivert. altså Idle/samme etasje, etc..
	elev->currentFloor = floor;
	if (should_stop(*elev)) {					//stopper hvis heisen skal stoppe, stopper ikke hvis ikke.
		open_doors(elev);						//NY STATE
	}
}

void fsm_request_btn_pressed(Elevator* elev , int floor, elev_button_type_t button){
	switch (elev->currentState) {	
		case State_Idle:
			q_add(floor, button, elev);	
			if(floor == elev->currentFloor && is_at_floor()) { //if request is at current floor, enter STATE_DoorsOpen
				open_doors(elev);
			}
			else {
				move(elev);					//Else, enter STATE_Move
			}
			break;
			
		case State_Move: 		//Add to queue, keep moving
			q_add(floor, button, elev);			
			break;
			
		case State_DoorsOpen: 	//if request is at current floor, re-enter STATE_DoorsOpen. 
			if(floor == elev->currentFloor) { 		
				open_doors(elev);
			}
			else {				//else add to queue
				q_add(floor, button, elev);	 
			}
			break;
		
		case State_Init:
		case State_Stop:
			break;
	}												
}

void fsm_stop_btn_pressed(Elevator* elev){
	elev->currentState = State_Stop;	
	//elev->currentDir = DIRN_STOP;
	elev_set_motor_direction(0);
	elev_set_stop_lamp(1);
	q_clear(elev);
	if (is_at_floor()){ 
		elev_set_door_open_lamp(1);
	}
	
	//busy wait while stop button pressed
	while(elev_get_stop_signal()) {	
	}
	
	//stop button released
	elev_set_stop_lamp(0);
	if (is_at_floor()) {
		open_doors(elev);
	}
	else {
		elev->currentState = State_Idle;
	}
}


void fsm_timer_timeout(Elevator* elev){
	timer_stop();
	elev_set_door_open_lamp(0); //door lamp = 0
	elev->currentState = State_Idle; 
	
	if (check_orders_above(*elev) || check_orders_below(*elev)) {		//checks if elevator should stay idle or move
		move(elev);
	}
} 

///////////////////////////////////////////////

void move(Elevator* elev) {
	elev->currentState = State_Move;
	elev->currentDir = set_direction(elev); 
	elev_set_motor_direction(elev->currentDir); //start motor
}

void open_doors(Elevator* elev) {
	elev->currentState = State_DoorsOpen;	//changes state
	elev_set_motor_direction(0);			//stops elevator
	q_complete(elev);						//clears orders and turns off order lamps
	
	elev_set_door_open_lamp(1);
	timer_start(3); 							//starts 3sec timer
}

elev_motor_direction_t set_direction(Elevator* elev) {
	elev_motor_direction_t newDirection = DIRN_UP;
	switch(elev->currentDir) {
		case(DIRN_UP): 											//if current/last direction was UP
			if (check_orders_above(*elev))  {
				newDirection = DIRN_UP;
				//elev->currentDir = DIRN_UP;
			}
			else if (check_orders_below(*elev)) {
				newDirection = DIRN_DOWN;
				//elev->currentDir = DIRN_DOWN;
			}
			break;
	
		case(DIRN_DOWN): 										//if current/last direction was DOWN

		case(DIRN_STOP):										//if last direction was STOP. Same as down. Doesnt matter.
			if (check_orders_below(*elev)) {
				newDirection = DIRN_DOWN;
				//elev->currentDir = DIRN_DOWN;
			}
			else if (check_orders_above(*elev))  {
				newDirection = DIRN_UP;
				//elev->currentDir = DIRN_UP;
			}
			break;

		default: break;
	}
	return newDirection;
}

bool is_at_floor() {
	return (elev_get_floor_sensor_signal() != -1);
}

bool is_btn_pressed(elev_button_type_t* button, int* floor) {
	for (int f= 0; f < N_FLOORS; f++) {
		for (int b = 0;  b < N_BUTTONS; b++) {
			
			if (!((b == 1 && f == 0) || (b == 0 && f == 3))) { //checks if button exists:   B=0: button call up, B=1: call down, B=2: command
				if (elev_get_button_signal(b, f)) {
					*button = b;
					*floor = f;
					return true;
				}
			}
		}
	}
	return false;
}
