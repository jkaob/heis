#include "events.h"
#include "fsm.h"

int arrive_at_floor(){
	switch(should_stop){		//sjekker om vi skal stoppe på etasjen den er i 
		case yes:
				open_doors(); //Doors open, timer on, lys på 
		case no:
				//fortsett i samme retning
		default:
	}
}

int request_btn_pressed(){

}

int stop_btn_pressed(){

}

int stop_btn_released(){

}


int timer_timeout(){
	elev_set_door_open_lamp(0); //door lamp = 0

	switch(current_dir) {
		case opp: //hvis bestillinger ovenfor: kjør opp
					//hvis ikke, sjekk ned. Hvis nede, bytt retning. 

		case ned: //hvis bestillinger nedenfor: kjør ned
					//hvis ikke sjekk opp. Hvis oppe, bytt retning.
	}
} 
