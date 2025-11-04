#include <stdint.h>

#include "drivers/vga.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/timer.h"
#include "cpu/io.h"
#include "lib/std.h"

static void tone(uint32_t nFrequence) {
	uint32_t Div;
	uint8_t tmp;

	Div = 1193180 / nFrequence;
	outb(0x43, 0xb6);
	outb(0x42, (uint8_t) (Div) );
	outb(0x42, (uint8_t) (Div >> 8));

	tmp = inb(0x61);
	if (tmp != (tmp | 3)) {
		outb(0x61, tmp | 3);
	}
}

static void shut_up() {
	uint8_t tmp = inb(0x61) & 0xFC;
	outb(0x61, tmp);
}

void on_keyboard(stack_frame_t frame) {
	outb(0x64, 0xFE);
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
	isr_handlers[0x21] = on_keyboard;
	asm("sti");

	puts("\x02 Finished IDT setup!\n");
	tone(880);
	sleep(75);
	tone(1397);
	sleep(75);
	shut_up();
}
