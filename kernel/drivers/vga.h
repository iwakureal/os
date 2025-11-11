#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define TEXT_MEMORY 0xB8000

#define VGA_COLS 80
#define VGA_ROWS 25
#define VGA_TOTAL VGA_COLS * VGA_ROWS
#define VGA_OFFSET(col, row) VGA_COLS * row + col

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
} vga_io_t;

typedef enum
{
	CURSOR_H = 14,
	CURSOR_L
} vga_register_t;

uint8_t vga_read_reg(vga_register_t reg);
void vga_write_reg(vga_register_t reg, uint8_t value);

uint16_t vga_get_cursor();
void vga_set_cursor(uint16_t cursor);

void vga_clear(vga_attribute_t attr);

int puts(const char *str);
int putc(char c);

#endif // VGA_H
