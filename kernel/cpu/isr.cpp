#include "isr.h"

#include <cstdint>

#include "cpu/io.h"
#include "cpu/idt.h"
#include "drivers/vga.h"

namespace isr {

const char *exceptions[] = {
	"Divide by zero",
	"Debug",
	"Non-maskable interrupt (NMI)",
	"Breakpoint",
	"INTO-triggered overflow",
	"Out of bounds",
	"Invalid opcode",
	"x87 FPU unavailable",
	"Double fault",
	"Coprocessor segment overrun",
	"Invalid TSS",
	"Segment not present",
	"Stack segment fault",
	"General protection fault",
	"Page fault",
	"Reserved",

	"x87 FPU fault",
	"Alignment check",
	"Machine check",
	"SIMD floating-point exception",
	"Virtualization exception",
	"Control protection exception",
	"Reserved",
	"Hypervisor injection exception",

	"VMM communication exception",
	"Security exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void init_default() {
	for (int i = 0; i < 47; i++) {
		idt::set_gate(i, reinterpret_cast<uint32_t>(default_handler));
	}

	io::out(0x20, 0x11);
	io::out(0xA0, 0x11);
	io::out(0x21, 0x20);
	io::out(0xA1, 0x28);
	io::out(0x21, 0x04);
	io::out(0xA1, 0x02);
	io::out(0x21, 0x01);
	io::out(0xA1, 0x01);
	io::out(0x21, 0x0);
	io::out(0xA1, 0x0);
}

__attribute__((interrupt, target("general-regs-only")))
void default_handler(frame_t* frame) {
	vga::puts("!!! Received interrupt, no idea which\n");
}

} /* namespace isr */
