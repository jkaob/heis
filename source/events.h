#ifndef EVENTS_H
#define EVENTS_H

#include <stdio.h>
#include <stdbool.h>
#include "fsm.h"

int main_loop();

void evt_arrive_at_floor(); //when elevator reaches floor

void evt_request_btn_pressed();  //when any request button is pressed

void evt_stop_btn_pressed(); 

void evt_stop_btn_released();

void evt_timer_timeout(); //on door timeout 


#endif