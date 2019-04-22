/**
* @file

	Contains main loop, initializing-function, 4 trigger events and 2 state transitions.
	Also contains 3 logic functions.
* @brief Final State Machine.
*/

#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdio.h>
#include "queue.h"
#include "state.h"
#include "timer.h"

/**
* @brief Main loop which contains the entire system logic.
* @param elev System structure
* @return exit code 0
*/
int fsm_main_loop(Elevator* elev);

/**
* @brief Initializing elevator system at start. Enters state @c Idle after initializing.
* @param elev System structure pointer
*/
void fsm_init_elevator(Elevator* elev);

/**
* @brief Event triggered by active floor sensor.
* @param elev System structure pointer
* @param floor Floor value from sensor signal
*/
void fsm_arrive_at_floor(Elevator* elev, int floor);

/**
* @brief Event triggered by button inputs. Changes elevator state to @c Move or @c Doors_Open depending on current state.
* @param elev System structure pointer
* @param floor Floor value from button input
* @param button Button value from button input
*/
void fsm_request_btn_pressed(Elevator* elev , int floor, elev_button_type_t button);

/**
* @brief Event triggered by stop button input.
*	Enter state @c Stop, stops polling buttons, clears queue and sets stop button lamp. Busy wait until button is released. 
* @param elev System structure pointer
*/
void fsm_stop_btn_pressed(Elevator* elev); 

/**
* @brief Event triggered on timer timeout. 
*	Stops timer, closes the door, enters state Idle if no further orders in queue.
* @param elev System structure pointer
*/
void fsm_timer_timeout(Elevator* elev);

/**
* @brief Enter state @c Move . Gets new direction and starts motor.
* @param elev System structure pointer
*/
void fsm_move(Elevator* elev); //Enter STATE_Move

/**
* @brief Enter state @c Doors_Open . Stops engine, open doors, start timer and clear requests at current floor. 
* @param elev System structure pointer
*/
void fsm_open_doors(Elevator* elev); //Enter STATE_DoorsOpen

/**
* @brief Returns @c true if floor sensor is active.
* @return 1 if elevator is at floor, 0 if not
*/
bool fsm_is_at_floor();

/**
* @brief Checks if any request button is pressed, and also returns which one if it is pressed (by reference).
* @param[out] button Button-value pointer
* @param[out] floor Floor-value pointer
* @return 1 if any request button is pressed, 0 if not
*/
bool fsm_is_btn_pressed(elev_button_type_t* button, int* floor);

/**
* @brief Gets new motor direction depending on current direction and queue. 
*	If stop was pressed, also considers  last direction before the stop button was pressed.
* @param elev System structure pointer
* @return new direction for elevator 
 */
elev_motor_direction_t fsm_get_direction(Elevator* elev);

#endif
