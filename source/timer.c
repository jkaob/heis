
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>


static double endTime;
int g_timerFlag = 0;

double timer_current_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 0.000001;
}

void timer_start(int dur) { 
    g_timerFlag = 1;
    endTime = dur + timer_current_time();
}

void timer_stop() {
    g_timerFlag = 0;
}

int timer_check() {
    return (timer_current_time() > endTime);
}
