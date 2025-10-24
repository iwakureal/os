#include "vga.h"

#include <stdint.h>
#include <stdbool.h>
#include "cpu/io.h"

namespace vga {

volatile cell_t (&text_memory)[80*25] = *reinterpret_cast<volatile cell_t (*)[80*25]>(TEXT_MEMORY);

namespace registers {
	uint8_t read(register_t reg) {
		io::out(CRTC_INDEX, reg);
		return io::in<uint8_t>(CRTC_DATA);
	}
	void write(register_t reg, uint8_t value) {
		io::out(CRTC_INDEX, reg);
		io::out(CRTC_DATA, value);
	}
} // namespace vga::registers
/*
namespace cursor {
	int get();
	void set(int cursor);
} // namespace vga::cursor

int puts(char *str);
int putc(char c);
*/
} // namespace vga
