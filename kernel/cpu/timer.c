#include "timer.h"

#include <stdint.h>
#include "cpu/io.h"

void timer_init(volatile uint32_t freq) {
	uint32_t divisor = BASE_CLOCK / freq;
	outb(0x43, 0x36);
	outb(0x40, (uint8_t)(divisor & 0xFF));
	outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}