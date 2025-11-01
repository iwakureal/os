#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define TEXT_MEMORY 0xB8000

typedef enum
{
	black,
	blue,
	green,
	aqua,
	red,
	magenta,
	brown,
	light_grey, // default
	grey,
	light_blue,
	light_green,
	light_aqua,
	light_red,
	light_magenta,
	light_yellow,
	white
} vga_color;

typedef struct __attribute__((packed))
{
	vga_color foreground : 4;
	vga_color background : 4;
} vga_attribute_t;

typedef struct __attribute((packed))
{
	char character;
	vga_attribute_t attribute;
} vga_cell_t;

extern vga_cell_t *const text_memory;
extern vga_attribute_t vga_default_color;

typedef enum
{
	CRTC_INDEX = 0x3D4,
	CRTC_DATA = 0x3D5
} io_t;

typedef enum
{
	CURSOR_H = 14,
	CURSOR_L
} vga_register_t;

uint8_t vga_read_reg(vga_register_t reg);
void vga_write_reg(vga_register_t reg, uint8_t value);

int vga_get_cursor();
void vga_set_cursor(int cursor);

void vga_clear(vga_attribute_t attr);

int puts(const char *str);
int putc(char c);

#endif // VGA_H
