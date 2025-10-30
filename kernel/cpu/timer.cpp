#include "timer.h"

#include <cstdint>
#include "cpu/io.h"

namespace timer {


void init(uint16_t freq) {
	uint32_t divisor = 1193180 / freq;
	io::out(0x43, 0b00110110);
	io::out(0x40, (uint8_t)(divisor & 0xFF));
	io::out(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}


} // namespace timer
