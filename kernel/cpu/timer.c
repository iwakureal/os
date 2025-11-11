#include "timer.h"

#include <stdint.h>
#include "cpu/io.h"
#include "cpu/isr.h"

int timer_count = 0;

void sleep(int ms) {
	timer_count = ms;
	while(timer_count > 0)
		_hlt();
}

void timer_default_callback(stack_frame_t frame) {
	if (timer_count == 0)
		return;
	timer_count--;
}

void timer_init(uint16_t divisor) {
	outb(0x43, 0x36);
	outb(0x40, (uint8_t)(divisor & 0xFF));
	outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
	isr_handlers[0x20] = timer_default_callback;
}
