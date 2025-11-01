#include "vga.h"

#include <cstdint>
#include <cstring>

#include "cpu/io.h"

namespace vga {

cell_t* const text_memory = reinterpret_cast<cell_t*>(TEXT_MEMORY);

attribute_t default_color = {color::light_grey, color::black};

namespace registers {

	uint8_t read(register_t reg) {
		io::outb(CRTC_INDEX, reg);
		return io::inb(CRTC_DATA);
	}

	void write(register_t reg, uint8_t value) {
		io::outb(CRTC_INDEX, reg);
		io::outb(CRTC_DATA, value);
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

void clear(attribute_t attr) {
	for (int i = 0; i < 80*25; i++) {
		text_memory[i].character = ' ';
		text_memory[i].attribute = attr;
	}
	cursor::set(0);
}

void scroll() {
	const cell_t empty = {' ', default_color};
	for (int i = 0; i < 80 * 25; i++)
	{
		if (i >= 80 * 24)
			text_memory[i] = empty;
		else
			text_memory[i] = text_memory[i + 80];
	}
	
}

int puts(const char *str) {
	int i = 0;
	int offset = cursor::get();
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

	if (offset >= 80 * 25) {
		scroll();
		offset -= 80;
	}

	cursor::set(offset);
	return offset;
}

} // namespace vga
