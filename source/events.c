#include "events.h"

int main_loop(Elevator* elev) {
	while(1) {
	
		{ //IF STOP BUTTON IS PRESSED
			if (elev_get_stop_signal()) {
			evt_stop_btn_pressed(&elev);
			}
		}
	
		{ //IF REQUEST BUTTON IS PRESSED 
			elev_button_type_t button;
			int floor;
			if (is_btn_pressed(&button, &floor)) { 
				evt_request_btn_pressed(&elev, floor, button);
			}
		}
	
		{	//IF ARRIVAL AT FLOOR
			if (elev_get_floor_sensor_signal() != -1) {
			evt_arrive_at_floor(&elev, elev_get_floor_sensor_signal());
			}
		}
	
		{	//IF TIMER TIMEOUT
			if () {
				evt_timer_timeout(&elev);
			}
		}
	}
	return 0;
}

int init_elevator(Elevator* elev) {
	elev->currentState = State_Init;
	
	while(elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_DOWN);
	}
	elev->currentDir = DIRN_DOWN;
	elev->currentFloor = elev_get_floor_sensor_signal();
	
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS); j++) {
			elev->queue[i][j] = 0;
		}
	}
	elev->currentState = State_Idle;
	return 1;
}



void evt_arrive_at_floor(Elevator* elev, int floor){		
	if (elev->currentFloor == floor) return; //hvis sensoren allerede har vært aktivert. altså Idle/samme etasje, etc..
	elev->currentFloor = floor;
	elev_set_floor_indicator(floor);
	if (should_stop(elev)) {			//stopper hvis heisen skal stoppe, stopper ikke hvis ikke.
		open_doors(&elev);							//NY STATE
	}
}

void evt_request_btn_pressed(Elevator* elev , int floor, elev_button_type_t button){
	switch (elev->Elev_State) {						//hvis IDLE: MOVE //hvis MOVE: MOVE //hvis DOORS_OPEN: //hvis STOPP: ----
		case State_Idle:
			q_add(floor, button, elev->queue);
			if(floor == elev->currentFloor && is_at_floor()) { //if request is at current floor, enter STATE_DoorsOpen
				open_doors();
			}
			else {
				move(elev);									//Enter state MOVE
			}
			break;
			
		case State_Move: 
			q_add(floor, button, elev->queue);				//Add to queue, keep moving
			break;
			
		case State_DoorsOpen: 
			if(floor == elev->currentFloor) { 				//if request is at current floor, re-enter STATE_DoorsOpen
				open_doors();
			}
			else {
				q_add(floor, button, elev->queue);			 //else add to queue
			}
			break;
		
		case State_Init:
		case State_Stop:
			break;
	}												
}

void evt_stop_btn_pressed(Elevator* elev){
	
}

void evt_stop_btn_released(Elevator* elev){
	
}


void evt_timer_timeout(Elevator* elev){
	elev_set_door_open_lamp(0); //door lamp = 0
} 
