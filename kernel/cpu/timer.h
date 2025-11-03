#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define BASE_CLOCK 1193182
#define HZ_TO_DIV(freq) BASE_CLOCK / freq

extern int timer_count;

void sleep(int ms);
void timer_init(uint16_t divisor);

#endif
