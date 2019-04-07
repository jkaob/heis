#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdio.h>
#include "elev.h"
#include "queue.h"
#include "state.h"

/**
  Enter Move-state. 
  @param elev System structure pointer
*/
void move(Elevator* elev); //Enter STATE_Move

/**
  Enter DoorsOpen-state. 
  @param elev System structure pointer
*/
void open_doors(Elevator* elev); //Enter STATE_DoorsOpen

/**
  Sets new direction depending on current direction and queue. 
  @param elev System structure pointer
*/
elev_motor_direction_t set_direction(Elevator* elev);


/**
  Returns true if floor sensor is active.
*/
bool is_at_floor();

/**
  Returns true if any request button is pressed. Changes param pointer values to button values.
  @param
*/
bool is_btn_pressed(elev_button_type_t* button, int* floor);

#endif