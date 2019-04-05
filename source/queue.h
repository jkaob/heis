#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include "state.h"

bool check_orders_above(Elevator elev);			//returns true if orders above
bool check_orders_below(Elevator elev); 	
bool should_stop(Elevator elev);				//checks queue and decides if to stop at new floor

void q_add(int floor, elev_button_type_t button, Elevator* elev);	//adds order to queue
void q_complete(Elevator* elev); 									//removes order
void q_clear(Elevator* elev);										//clears queue

#endifa