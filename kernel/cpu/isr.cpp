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
	"Reserved",

	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Hypervisor injection exception",
	"VMM communication exception",
	"Security exception",
	"Reserved",

	"PIT",
	"Keyboard",
	"Cascade",
	"COM2",
	"COM1",
	"LPT2",
	"Floppy",
	"LPT1",
	"CMOS RTC",
	"Peripheral 0",
	"Peripheral 1",
	"Peripheral 2",
	"PS/2 Mouse",
	"FPU",
	"Primary ATA Disk",
	"Secondary ATA Disk",
};

void init_default() {
	for (int i = 0; i < 256; i++) {
		idt::set_gate(i, stub_table[i]);
	}

	io::out(0x20, 0x11);
	io::wait();
	io::out(0xA0, 0x11);
	io::wait();
	io::out(0x21, 0x20);
	io::wait();
	io::out(0xA1, 0x28);
	io::wait();
	io::out(0x21, 0x04);
	io::wait();
	io::out(0xA1, 0x02);
	io::wait();
	io::out(0x21, 0x01);
	io::wait();
	io::out(0xA1, 0x01);
	io::wait();
	io::out(0x21, 0x00);
	io::wait();
	io::out(0xA1, 0x00);
	io::wait();
}

extern "C" void default_handler(frame_t frame) {
	int id = frame.int_num;
	vga::puts("!!! Received interrupt: ");
	if (id >= 32 && id < 48) {
		vga::puts("[IRQ] ");
	}

	if (id < 48) {
		vga::puts(exceptions[id]);
	} else {
		vga::puts("<unknown>");
	}
	vga::puts("\n");

	if (id >= 40) {
		io::out(0xA0, 0x20);
	}
	io::out(0x20, 0x20);
}

} /* namespace isr */
