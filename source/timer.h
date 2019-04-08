#ifndef timer_h
#define timer_h

#include <stdio.h>
extern int g_timerFlag;
// semigenerelt vil oppsettet til en timer bestå av:
    // sett verdi i timer-register (basert på nåverdi og intervall)
    // aktiver timer-interrupt i timer-enheten
    // aktiver timerens interrupt i interrupt controller
    // lag ISR som bekrefter, tar aksjon og evt. oppdaterer timer-register
double current_time();
void timer_on(int sec);
void timer_off();
int timer_funk();


#endif /* timer_h */
