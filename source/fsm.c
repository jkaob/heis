#include "fsm.h"

void open_doors() {
	elev_set_motor_direction(0);
	elev_set_door_open_lamp(1);
	
	timer_start(); //må defineres
}