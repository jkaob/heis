#include "events.h"

void evt_arrive_at_floor(Elevator* elev, int floor){
	elev->currentFloor = floor;
	elev_set_floor_indicator(floor);
	if (should_stop(elev)) {			//stopper hvis heisen skal stoppe, stopper ikke hvis ikke.
		open_doors();							//NY STATE
	}
}

void evt_request_btn_pressed(Elevator* elev , int floor, elev_button_type_t button){
	switch (elev->Elev_State) {						//hvis IDLE: MOVE //hvis MOVE: MOVE //hvis DOORS_OPEN: //hvis STOPP: ----
		case State_Idle:
			if(floor == elev->currentFloor && is_at_floor(elev)) { //if request is at current floor, enter STATE_DoorsOpen
				open_doors();
			//mulig fail her: går inn i open doors igjen, uten å legge inn bestilling på samme etasje. hvordan påvirker det køsystemt?
			}
			else {
				q_add(floor, button, elev->queue);
				move(elev);	//denne i FSM ? Må implementeres. 
			}
			
			break;
			
		case State_Move: 
			q_add(floor, button, elev->queue);	//Add to queue, keep moving
			break;
			
		case State_DoorsOpen: 
			if(floor == elev->currentFloor) { //if request is at current floor, re-enter STATE_DoorsOpen
				open_doors();
			}
			else {
				q_add(floor, button, elev->queue); //else add to queue
			}
			break;
			
		case State_Stop:
			break;
	}												
}

void evt_stop_btn_pressed(){
	
}

void evt_stop_btn_released(){
	
}


void evt_timer_timeout(Elevator* elev){
	elev_set_door_open_lamp(0); //door lamp = 0
	switch(elev->currentDir) 
} 
