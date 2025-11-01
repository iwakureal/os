#include "vga.h"

#include <stdint.h>
#include "cpu/io.h"

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

int vga_get_cursor()
{
	return vga_read_reg(CURSOR_H) << 8 | vga_read_reg(CURSOR_L);
}

void vga_set_cursor(int cursor)
{
	vga_write_reg(CURSOR_H, (uint8_t)(cursor >> 8));
	vga_write_reg(CURSOR_L, (uint8_t)(cursor & 0xFF));
}

void vga_clear(vga_attribute_t attr)
{
	for (int i = 0; i < 80 * 25; i++)
	{
		text_memory[i].character = ' ';
		text_memory[i].attribute = attr;
	}
	vga_set_cursor(0);
}

void vga_scroll()
{
	const vga_cell_t empty = {' ', vga_default_color};
	for (int i = 0; i < 80 * 25; i++)
	{
		if (i >= 80 * 24)
			text_memory[i] = empty;
		else
			text_memory[i] = text_memory[i + 80];
	}
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
	int offset = vga_get_cursor();

	switch (c)
	{
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

	if (offset >= 80 * 25)
	{
		vga_scroll();
		offset -= 80;
	}

	vga_set_cursor(offset);
	return offset;
}