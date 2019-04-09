
#include "timer.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static double endTime;
int g_timerFlag = 0;

double current_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 0.000001;
}

void timer_start(int dur) { // starter når dørene åpnes
    g_timerFlag = 1;
    endTime = dur + time(NULL);
}

void timer_stop() {
    g_timerFlag = 0;
}

int timer_check() {
    return (current_time() > endTime);
}