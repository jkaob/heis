#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdio.h>
#include "elev.h"
#include "queue.h"
#include "state.h"
#include "timer.h"

/**
  @brief Main loop which contains the entire logic.
  @param elev System structure
  @return exit code 1 
*/
int fsm_main_loop(Elevator* elev);

/**
  Initializing elevator system at start.
  @param elev System structure pointer
*/
int fsm_init_elevator(Elevator* elev);

/**
  Event triggered by active floor sensor.
  @param elev System structure pointer
  @param floor Floor value from sensor signal
*/
void fsm_arrive_at_floor(Elevator* elev, int floor);

/**
  Event triggered by button inputs. Changes elevator state to Move or Doors_Open depending on current state.
  @param elev System structure pointer
  @param floor Floor value from button input
  @param button Button value from button input
*/
void fsm_request_btn_pressed(Elevator* elev , int floor, elev_button_type_t button);

/**
  Event triggered by stop button input.
  @param elev System structure pointer
*/
void fsm_stop_btn_pressed(Elevator* elev); 

/**
  Event triggered on timer timeout.
  @param elev System structure pointer
*/
void fsm_timer_timeout(Elevator* elev);




/////////////////////////////////////////////////////////////


/**
  Enter Move-state. 
  @param: elev System structure pointer
*/
void move(Elevator* elev); //Enter STATE_Move

/**
  Enter DoorsOpen-state. 
  @param: elev System structure pointer
*/
void open_doors(Elevator* elev); //Enter STATE_DoorsOpen

/**
  Gets new direction depending on current direction and queue. 
  @param: elev System structure pointer
  @return: new direction
*/
elev_motor_direction_t get_direction(Elevator* elev);


/**
  Returns true if floor sensor is active.
*/
bool is_at_floor();

/**
  Returns true if any request button is pressed. Changes param pointer values to button values.
  @param: button Button-value pointer
  @param: floor Floor-value pointer
*/
bool is_btn_pressed(elev_button_type_t* button, int* floor);

#endif