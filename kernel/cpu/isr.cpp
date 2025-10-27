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
	for (int i = 0; i < 32; i++) {
		idt::set_gate(i, reinterpret_cast<void(*)()>(0));
	}
}
/*
__attribute__((interrupt))
void default_handler() {
	vga::puts("!!! Received interrupt, no idea which");
}*/

} /* namespace isr */
