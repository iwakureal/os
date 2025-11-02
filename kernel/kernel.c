#include <stdint.h>

#include "drivers/vga.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/timer.h"

void kmain()
{
	vga_default_color = (vga_attribute_t){light_green, black};
	vga_clear(vga_default_color);
	puts("Hello, world!\n");

	idt_descriptor_t desc = {sizeof(idt) - 1, (uint32_t)&idt};

	isr_init();
	lidt(&desc);
	timer_init(65535);
	asm("sti");

	puts("\x02 Finished IDT setup!\n");
}
