#include <stdint.h>
#include "drivers/vga.h"

extern "C" void kmain() {
	for(auto& cell : vga::text_memory) {
		cell.attribute.foreground = vga::color::white;
		cell.attribute.background = vga::color::blue;
	}
}
