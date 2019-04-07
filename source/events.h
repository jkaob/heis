#ifndef EVENTS_H
#define EVENTS_H

#include <stdio.h>
#include <stdbool.h>
#include "fsm.h"

/**
  Main loop which contains the entire logic.
  @param elev System structure
*/
int main_loop(Elevator* elev);

/**
  Initializing elevator system at start.
  @param elev System structure pointer
*/
int init_elevator(Elevator* elev);

/**
  Event triggered by active floor sensor.
  @param elev System structure pointer
  @param floor Floor value from sensor signal
*/
void evt_arrive_at_floor(Elevator* elev, int floor);

/**
  Event triggered by button inputs. Changes elevator state to Move or Doors_Open depending on current state.
  @param elev System structure pointer
  @param floor Floor value from button input
  @param button Button value from button input
*/
void evt_request_btn_pressed(Elevator* elev , int floor, elev_button_type_t button);

/**
  Event triggered by stop button input.
  @param elev System structure pointer
*/
void evt_stop_btn_pressed(Elevator* elev); 

/**
  Event triggered by stop button release input.
  @param elev System structure pointer
*/
void evt_stop_btn_released(Elevator* elev);

/**
  Event triggered on timer timeout.
  @param elev System structure pointer
*/
void evt_timer_timeout(Elevator* elev);


#endif