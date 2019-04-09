#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include "state.h"


/**
  Returns true if there are orders above current floor in the queue. 
  @param elev System structure
*/
bool q_check_orders_above(Elevator elev);

/**
  Returns true if there are orders below current floor in the queue. 
  @param elev System structure
*/
bool q_check_orders_below(Elevator elev); 

/**
  Returns true if there are orders in the same direction or if passenger wants to get off at current floor. 
  @param elev System structure
*/	
bool q_should_stop(Elevator elev);


/**
  Adds order to queue and sets order lamp to 1. 
  @param floor Floor value from input
  @param button Button value from input 
  @param elev System structure pointer
*/
void q_add(int floor, elev_button_type_t button, Elevator* elev);

/**
  Removes orders at current floor when completed and sets the lights to 0.
  @param elev System structure pointer
*/
void q_complete(Elevator* elev); 

/**
  Clears the entire queue and sets all order lamps to 0.
  @param elev System structure pointer
*/
void q_clear(Elevator* elev);

#endif