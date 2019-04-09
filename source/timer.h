#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <sys/time.h>
#include <stdio.h>
extern int g_timerFlag;
// semigenerelt vil oppsettet til en timer bestå av:
    // sett verdi i timer-register (basert på nåverdi og intervall)
    // aktiver timer-interrupt i timer-enheten
    // aktiver timerens interrupt i interrupt controller
    // lag ISR som bekrefter, tar aksjon og evt. oppdaterer timer-register

double current_time();

void timer_start(int dur);

void timer_stop();

int timer_check();

#endif /* timer_h */
