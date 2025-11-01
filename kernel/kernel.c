#include <stdint.h>

#include "drivers/vga.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/timer.h"

void commence_idt_torture() {
	asm("int $0");
	asm("int $1");
	asm("int $2");
	asm("int $3");
	asm("int $4");
	asm("int $5");
	asm("int $6");
	asm("int $7");
	asm("int $9");
	asm("int $255");
}

void kmain() {
	vga_default_color = (vga_attribute_t){light_green, black};
	vga_clear(vga_default_color);
	puts("Hello, world!\n");

	idt_descriptor_t desc = {sizeof(idt) -1, (uint32_t)&idt};

	isr_init();
	lidt(&desc);
	timer_init(1);
	asm("sti");

	puts("\x02 Finished IDT setup!!! Now let's torture it with a bunch of interrupts\n");
	commence_idt_torture();
}
