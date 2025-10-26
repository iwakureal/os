#include "vga.h"

#include <stdint.h>
#include <stdbool.h>
#
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

namespace cursor {

	int get() {
		return registers::read(registers::CURSOR_H) << 8 | registers::read(registers::CURSOR_L);
	}

	void set(int cursor) {
		registers::write(registers::CURSOR_H, (uint8_t)(cursor >> 8));
		registers::write(registers::CURSOR_L, (uint8_t)(cursor & 0xFF));
	}

} // namespace vga::cursor

void clear() {
	for (auto& cell : text_memory) {
		cell.character = ' ';
	}
	cursor::set(0);
}

int puts(char *str) {
	int i = 0;
	int offset;
	while (str[i] != 0) {
		offset = putc(str[i++]);
	}
	return offset;
}

int putc(char c) {
	int offset = cursor::get();

	switch (c) {
		case '\n':
			offset = 80 * (offset / 80 + 1);
			break;
		case '\b':
			text_memory[offset].character = ' ';
			break;
		default:
			text_memory[offset].character = c;
			offset++;
	}

	cursor::set(offset);
	return offset;
}

} // namespace vga
