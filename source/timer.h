/**
* @file
* @brief Timer for finite state machine.
*/

#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

/**
* Global variable used for checking if timer has just recently timed out or not. 
*/
extern int g_timerFlag;

/**
*  @brief Calculates current time for the computer.
*  @return current time
*/
double timer_current_time();

/**
*  @brief Sets @p g_timerFlag to 1, activating the timer.
*  @param dur Timer duration in seconds.
*/
void timer_start(int dur);

/**
*  @brief Sets @p g_timerFlag to 0, deactivating the timer. 
*/
void timer_stop();

/**
*  @brief Checks whether or not timer is timed out.
*  @return 1 if timer is timed out, 0 if not.
*/
int timer_check();

#endif
