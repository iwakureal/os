#ifndef VGA_H
#define VGA_H

#include <stdint.h>

namespace vga {

const int VIDEO_MEMORY = 0xA0000;
const int TEXT_MEMORY = 0xB8000;

enum class color : uint8_t {
	black,
	blue,
	green,
	aqua,
	red,
	magenta,
	brown,
	light_grey,	// default
	grey,
	light_blue,
	light_green,
	light_aqua,
	light_red,
	light_magenta,
	light_yellow,
	white
};

struct attribute_t {
	color foreground : 4;
	color background : 4;
} __attribute__((packed));

struct cell_t {
	char character;
	attribute_t attribute;
} __attribute__((packed));

extern volatile cell_t (&text_memory)[80*25];

namespace registers {
	enum io_t : uint16_t {
		CRTC_INDEX = 0x3D4,
		CRTC_DATA = 0x3D5
	};

	enum register_t : uint8_t {
		CURSOR_H = 14,
		CURSOR_L
	};

	uint8_t read(register_t reg);
	void write(register_t reg, uint8_t value);

} // namespace vga::registers

namespace cursor {
	int get();
	void set(int cursor);

} // namespace vga::cursor

void clear();

int puts(char *str);
int putc(char c);

} // namespace vga

#endif // VGA_H
