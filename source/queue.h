#include <stdio.h>
#include "elev.h"

/*typedef struct{
/	int ord_flr; //floor of order
	int ord_dir; //direction of order
} Order		//overkill?*/




extern int queue[N_FLOORS][N_BUTTONS];  //2D array:   [index = Actual floor - 1] | order_up | order_down | cab_btn |


bool check_orders_above(int currentFloor, int** queue);
bool check_orders_below(int currentFloor, int** queue); 	// disse to går gjennom kø-listen

void q_add(int floor, elev_button_type_t button, int** queue);//tar inn en bestilling: etasje og retning
void q_complete(int currentFloor, int** queue); //fjerner en ordre 
void q_clear(int** queue);						//tømmer bestillinger
