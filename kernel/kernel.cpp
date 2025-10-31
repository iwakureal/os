#include <cstdint>

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

extern "C" void kmain() {
	vga::attribute_t color = {vga::color::light_green, vga::color::black};
	vga::clear(color);
	vga::puts("Hello, world!\n");

	idt::descriptor_t desc;
	desc.size = 256 * sizeof(idt::gate_t) - 1;
	desc.offset = (uint32_t)idt::idt;

	isr::init_default();
	idt::lidt(&desc);
	timer::init(1);
	asm("sti");

	vga::puts("\x02 Finished IDT setup!!! Now let's torture it with a bunch of interrupts\n");
	commence_idt_torture();
}
