#include <cstdint>

#include "drivers/vga.h"
#include "cpu/idt.h"
#include "cpu/isr.h"

extern "C" void kmain() {
	vga::attribute_t color = {vga::color::light_green, vga::color::black};
	vga::clear(color);
	vga::puts("Hello, world!\n");

	idt::descriptor_t desc = {
		256 * sizeof(idt::gate_t) - 1,
		(uint32_t)idt::idt
	};

	isr::init_default();
	idt::lidt(&desc);

	vga::puts("\x02 Finished IDT setup!!!");
}
