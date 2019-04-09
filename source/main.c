#include "elev.h"
#include "fsm.h"
#include <stdio.h>
#include <stdbool.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
      //  printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    //printf("Press STOP button to stop elevator and exit program.\n");
    elev_set_motor_direction(DIRN_UP);
	
	//int a = 100000;
	
	Elevator e;
	fsm_init_elevator(&e);
	fsm_main_loop(&e);

	//printf(elev_get_floor_sensor_signal());
 
 
	
   /* while (1) {
		
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }
        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }*/

    return 0;
}
