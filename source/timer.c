
#include "timer.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static int timerActive;
static double endTime;
int g_timerFlag;

double current_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec * 100000 + (double)t.tv_usec; // -> ms ?
}


int timer_start(int dur) { // starter når dørene åpnes
	g_timerFlag = 1;
	endTime = dur + current_time();
	
	
	return (current_time() > endTime);
}