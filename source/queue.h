#include <stdio.h>
#include "elev.h"


extern int queue[N_FLOORS][N_BUTTONS];  //2D array:   [index = Actual floor - 1] | order_up | order_down | cab_btn |


bool check_orders_above(int currentFloor, int** queue);
bool check_orders_below(int currentFloor, int** queue); 	
elev_motor_direction_t set_direction(int currentFloor, int** queue);	//chooses (new) direction



void q_add(int floor, elev_button_type_t button, int** queue);	//adds order to queue
void q_complete(int currentFloor, int** queue); //removes order
void q_clear(int** queue);						//clears queue
