#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define BASE_CLOCK 1193182

void timer_init(volatile uint32_t freq);

#endif
