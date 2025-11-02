#include "timer.h"

#include <stdint.h>
#include "cpu/io.h"

void timer_init(uint16_t divisor) {
	outb(0x43, 0x36);
	outb(0x40, (uint8_t)(divisor & 0xFF));
	outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}