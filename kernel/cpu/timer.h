#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define BASE_CLOCK 105/88 * 1000000
#define HZ_TO_DIV(freq) BASE_CLOCK / freq

void timer_init(uint16_t divisor);

#endif
