#include <stdint.h>
#include "drivers/vga.h"

extern "C" void kmain() {
	vga::clear();
	for(auto& cell : vga::text_memory) {
		cell.attribute.foreground = vga::color::light_green;
		cell.attribute.background = vga::color::black;
	}
	vga::puts("Hello, world!\n");
}
