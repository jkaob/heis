#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdio.h>
#include "elev.h"
#include "queue.h"
#include "state.h"


void move(Elevator elev); //Enter STATE_Move

void open_doors(); //Enter STATE_DoorsOpen

elev_motor_direction_t set_direction(Elevator* elev);	//chooses (new) direction

bool is_at_floor(); //checks if at floor

void poll_buttons();

#endif