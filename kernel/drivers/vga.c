#include "vga.h"

#include <stdint.h>
#include "cpu/io.h"
#include "lib/std.h"

vga_cell_t *const text_memory = (vga_cell_t *)TEXT_MEMORY;
vga_attribute_t vga_default_color = {light_grey, black};

uint8_t vga_read_reg(vga_register_t reg)
{
	outb(CRTC_INDEX, reg);
	return inb(CRTC_DATA);
}

void vga_write_reg(vga_register_t reg, uint8_t value)
{
	outb(CRTC_INDEX, reg);
	outb(CRTC_DATA, value);
}

uint16_t vga_get_cursor()
{
	return vga_read_reg(CURSOR_H) << 8 | vga_read_reg(CURSOR_L);
}

void vga_set_cursor(uint16_t cursor)
{
	vga_write_reg(CURSOR_H, (uint8_t)(cursor >> 8));
	vga_write_reg(CURSOR_L, (uint8_t)(cursor & 0xFF));
}

void vga_clear(vga_attribute_t attr)
{
	for (int i = 0; i < 16384; i++)
	{
		text_memory[i].character = ' ';
		text_memory[i].attribute = attr;
	}
	vga_set_cursor(0);
}

void vga_scroll()
{
	vga_cell_t empty = {' ', vga_default_color};
	movsb(text_memory,
		text_memory + VGA_OFFSET(0, 1),
		sizeof(vga_cell_t) * 80 * 24
	);
	stosw(
		text_memory + VGA_OFFSET(0, 24),
		*(uint16_t*)&empty,
		80 * 1
	);

}

int puts(const char *str)
{
	int i = 0;
	int offset = vga_get_cursor();
	while (str[i] != 0)
	{
		offset = putc(str[i++]);
	}
	return offset;
}

int putc(char c)
{
	uint16_t offset = vga_get_cursor();

	switch (c)
	{
	case '\n':
		offset = VGA_COLS * (offset / VGA_COLS + 1);
		break;
	case '\b':
		text_memory[offset].character = ' ';
		break;
	default:
		text_memory[offset].character = c;
		text_memory[offset].attribute = vga_default_color;
		offset++;
	}

	if (offset >= VGA_TOTAL) {
		vga_scroll();
		offset -= VGA_COLS;
	}

	text_memory[offset].attribute = vga_default_color;
	vga_set_cursor(offset);
	return offset;
}
