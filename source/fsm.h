#include <stdio.h>
#include "elev.h"

typedef enum {
	State_Idle
	State_Move
	State_DoorOpen
	State_Stop
} ElevState


typedef struct {
	int current_floor;
	elev_motor_direction_t current_dir;	//enum from "elev.h"
	ElevState current_state;
	bool orders_above;
	bool orders_below;
} Elevator


void open_doors();

void poll_buttons();