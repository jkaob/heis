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
	
	Elevator e;
	fsm_init_elevator(&e);
	fsm_main_loop(&e);

    return 0;
}
