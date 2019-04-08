#include "events.h"
#include "fsm.h"

void arrive_at_floor(Elevator* elev){
	if (should_stop(elev->currentFloor)) {			//stopper hvis heisen skal stoppe, stopper ikke hvis ikke.
		doors_open();							//NY STATE
	}
}

void request_btn_pressed(Elevator* elev){
	switch (elev->Elev_State) {						//hvis IDLE: MOVE //hvis MOVE: MOVE //hvis DOORS_OPEN: //hvis STOPP: ----
		case State_Idle:
		case State_Move:
		case State_DoorsOpen: 
		case State_Stop:
													
	}												
}

void stop_btn_pressed(){
	
}

void stop_btn_released(){
	
}


void timer_timeout(){
	elev_set_door_open_lamp(0); //door lamp = 0

} 
