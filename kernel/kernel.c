#include <stdint.h>

#include "drivers/vga.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/timer.h"
#include "cpu/io.h"
#include "lib/std.h"

char scan_buf[30];



void on_keyboard(stack_frame_t frame) {
	uint8_t scancode = inb(0x60);
	puts("!!! Keyboard scancode: ");
	if (scancode == 0xE0) {
		scancode = inb(0x60);
		puts("0xE0 + ");
	}
	puts("0x");
	puts(itoa(scancode, scan_buf, 16));
	putc('\n');
}

void kmain()
{
	vga_default_color = (vga_attribute_t){light_green, black};
	vga_clear(vga_default_color);
	puts("Hello, world!\n");

	idt_descriptor_t desc = {sizeof(idt) - 1, (uint32_t)&idt};

	isr_init();
	lidt(&desc);
	timer_init(1193);
	isr_handlers[33] = on_keyboard;
	asm("sti");

	puts("\x02 Finished IDT setup!\n");
	sleep(5000);
	puts("sleep(5000) completed\n");
}
