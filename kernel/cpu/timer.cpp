#include "timer.h"

#include <cstdint>
#include "cpu/io.h"

namespace timer {


void init(volatile uint32_t freq) {
	uint32_t divisor = BASE_CLOCK / freq;
	io::outb(0x43, 0x36);
	io::outb(0x40, (uint8_t)(divisor & 0xFF));
	io::outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}


} // namespace timer
