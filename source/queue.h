/**
* @file
* @brief Queue system for elevator. Contains logic for finite state machine.
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include "state.h"


/**
*  @brief Iterates the queue, and checks if there are orders above current floor.
*  @param elev System structure
*  @return 1 if @p elev.queue contains orders above, 0 if not
*/
bool q_check_orders_above(Elevator elev);

/**
*  @brief Iterates the queue, and checks if there are orders below current floor.
*  @param elev System structure
*  @return 1 if @p elev.queue contains orders below, 0 if not
*/
bool q_check_orders_below(Elevator elev); 

/**
*  @brief Returns @c true if there are orders in the same direction or if passenger wants to get off at current floor. 
*	Also returns @c true if there are no further orders in the queue.
*  @param elev System structure
*  @return 1 if elevator should stop, 0 if not.
*/	
bool q_should_stop(Elevator elev);





/**
*  @brief Adds order to queue and sets order lamp to 1. 
*  @param floor Floor value from input
*  @param button Button value from input 
*  @param elev System structure pointer
*/
void q_add(int floor, elev_button_type_t button, Elevator* elev);

/**
*  @brief Removes orders at current floor when completed and sets the lights to 0.
*  @param elev System structure pointer
*/
void q_complete(Elevator* elev); 

/**
*  @brief Clears the entire queue and sets all order lamps to 0.
*  @param elev System structure pointer
*/
void q_clear(Elevator* elev);



#endif
