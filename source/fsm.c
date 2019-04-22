#include <stdio.h>
#include "fsm.h"

int g_emergencyFlag;

int fsm_main_loop(Elevator* elev) {
	while(1) {
	//Main loop constantly checking the 4 triggers
	
		{ //IF STOP BUTTON IS PRESSED
			if (elev_get_stop_signal()) {
				fsm_stop_btn_pressed(elev);
			}
		}
	
		{ //IF REQUEST BUTTON IS PRESSED 
			elev_button_type_t btn;
			int flr;
			if (fsm_is_btn_pressed(&btn, &flr)) { 
				fsm_request_btn_pressed(elev, flr, btn);
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

void fsm_init_elevator(Elevator* elev) {
	//Enter state INIT 
	elev->currentState = State_Init;
	g_timerFlag = 0;
	g_emergencyFlag = 0;
	elev_set_motor_direction(DIRN_DOWN);

	while(elev_get_floor_sensor_signal() == -1) {
		//Move down to nearest floor and then stop 
	}
	elev_set_motor_direction(DIRN_STOP);
	
	//Sets current direction to DOWN, as the stop button has not been pressed. 
	elev->currentDir = DIRN_DOWN;
	
	//Sets current floor and floor indicator
	elev->currentFloor = elev_get_floor_sensor_signal();
	elev_set_floor_indicator(elev_get_floor_sensor_signal());
	
	//Initializing the queue matrix, clearing all orders.
	for (int i = 0; i < N_FLOORS; i++) {
		for (int j = 0; j < N_BUTTONS; j++) {
			elev->queue[i][j] = 0;
		}
	}
	//Enter state IDLE after initializing 
	elev->currentState = State_Idle;
	return;
}



void fsm_arrive_at_floor(Elevator* elev, int floor){
	//if floor sensor is already activated, meaning elevator is idle or waiting, return.
	if (elev->currentFloor == floor && !g_emergencyFlag) 
		return; 	
	//Resetting the emergency flag for the stop inbetween floors-situation.
	g_emergencyFlag = 0;
	
	//in case of bug or timer fault
	if (floor!= -1) {	
		elev->currentFloor = floor;
		elev_set_floor_indicator(floor);
	}
	//enter State_DoorsOpen if supposed to
	if (q_should_stop(*elev))
		fsm_open_doors(elev);
}

void fsm_request_btn_pressed(Elevator* elev , int floor, elev_button_type_t button){
	switch (elev->currentState) {	

		case State_Idle:
			//add request to queue
			q_add(floor, button, elev);	

			//if request is at current floor, enter STATE_DoorsOpen
			if(floor == elev->currentFloor && fsm_is_at_floor())
				fsm_open_doors(elev);
			//Else, enter STATE_Move
			else 
				fsm_move(elev);		
			break;
			
		case State_Move: 
			//Add to queue, keep moving
			q_add(floor, button, elev);		
			break;
			
		case State_DoorsOpen: 	
			//if request is at current floor, re-enter STATE_DoorsOpen. 
			if(floor == elev->currentFloor)	
				fsm_open_doors(elev);
			
			//else add to queue
			else			
				q_add(floor, button, elev);	 
			break;
		
		//If State_Init or State_Stop, no event on button press
		case State_Init:
		case State_Stop:
			break;
	}												
}

void fsm_stop_btn_pressed(Elevator* elev){
	//Stop elevator and change state
	elev->currentState = State_Stop;
	elev_set_motor_direction(0);
	//Toggles stop lamp and clears queue
	elev_set_stop_lamp(1);
	q_clear(elev);
	//If elevator is at floor, open the doors 
	if (fsm_is_at_floor())
		elev_set_door_open_lamp(1);
	
	//If this is the first time activating STOP between floors, save last direction and floor
	if (!g_emergencyFlag) {	
		elev->emergencyDir = elev->currentDir;
		elev->emergencyFloor = elev->currentFloor;
		g_emergencyFlag = 1;	//EmergencyFlag is activated, activate floor sensor to reset
	}
	elev->currentDir = DIRN_STOP;
	//busy wait while stop button pressed
	while(elev_get_stop_signal()) {	
	}
	
	//stop button released. If elevator is at floor, enter State_DoorsOpen, if not, enter State_Idle. 
	elev_set_stop_lamp(0);
	if (fsm_is_at_floor())
		fsm_open_doors(elev);
	else 
		elev->currentState = State_Idle;
}


void fsm_timer_timeout(Elevator* elev){
	//Stops timer, close doors and enter state Idle.
	timer_stop();
	elev_set_door_open_lamp(0);
	elev->currentState = State_Idle; 
	
	//checks if elevator should stay idle or move
	if (q_check_orders_above(*elev) || q_check_orders_below(*elev))	
		fsm_move(elev);
} 


void fsm_move(Elevator* elev) {
	elev->currentState = State_Move;
	
	//Gets and sets new direction
	elev->currentDir = fsm_get_direction(elev);
	elev_set_motor_direction(elev->currentDir);
}

void fsm_open_doors(Elevator* elev) {
	elev->currentState = State_DoorsOpen;
	
	//Stops motor
	elev_set_motor_direction(0);	
	
	//Completes the orders at the current floor 
	q_complete(elev);
	
	//starts 3sec timer and opens door 
	elev_set_door_open_lamp(1);
	timer_start(3); 							
}


bool fsm_is_at_floor() {
	return (elev_get_floor_sensor_signal() != -1);
}

bool fsm_is_btn_pressed(elev_button_type_t* button, int* floor) {
	for (int f= 0; f < N_FLOORS; f++) {
		for (int b = 0;  b < N_BUTTONS; b++) {

			//checks if button exists:   B=0: button call up, B=1: call down, B=2: command
			if (!((b == 1 && f == 0) || (b == 0 && f == 3))) { 
				if (elev_get_button_signal(b, f)) {
					*button = b;		//changes pointer values
					*floor = f;
					return true;
				}
			}
		}
	}
	return false;
}



elev_motor_direction_t fsm_get_direction(Elevator* elev) {
    
    switch(elev->currentDir) {
            //if current/last direction was UP
        case(DIRN_UP):
			//Prioritizes orders in the same direction as current.
            if (q_check_orders_above(*elev))
                return DIRN_UP;
            else if (q_check_orders_below(*elev))
                return DIRN_DOWN;
            
            //if current/last direction was DOWN
        case(DIRN_DOWN):
            if (q_check_orders_below(*elev))
                return DIRN_DOWN;
            else if (q_check_orders_above(*elev))
                return DIRN_UP;
            
            //if current/last direction was STOP, meaning Stop was pushed
        case(DIRN_STOP):
            
            //if elevator was stopped between floors
            if (!fsm_is_at_floor()) { 
                
                //if last direction before stopping was UP (elevator is above current floor):
                if (elev->emergencyDir == DIRN_UP) {
                    
                    if(q_check_orders_above(*elev))
                        return DIRN_UP;
                    
					//Checks if there are any new requests at floor last passed.
                    for (int i = 0; i < N_BUTTONS; i++) {
                        if (elev->queue[elev->currentFloor][i])
                            return DIRN_DOWN;
                    }
                }
                //if last direction before stopping was DOWN (elevator is below current floor):
                if (elev->emergencyDir == DIRN_DOWN) {
                    
                    if(q_check_orders_below(*elev))
                        return DIRN_DOWN;
                    
					//Checks if there are any new requests at floor last passed.
                    for (int i = 0; i < N_BUTTONS; i++) {
                        if (elev->queue[elev->currentFloor][i])
                            return DIRN_UP;
                    }
                }
            }
            
			//if elevator is at a floor, meaning it should behave normally. 
            if(q_check_orders_above(*elev))
                return DIRN_UP;
            
            if(q_check_orders_below(*elev))
                return DIRN_DOWN;
            
            return DIRN_STOP;
            
        default:
            return DIRN_STOP;
    }
}
