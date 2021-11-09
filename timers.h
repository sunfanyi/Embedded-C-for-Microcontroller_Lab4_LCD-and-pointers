#ifndef _timers_H
#define _timers_H

#include <xc.h>

#define _XTAL_FREQ 64000000

void Timer0_init();
void Timer0_restart(unsigned char score);

#endif
