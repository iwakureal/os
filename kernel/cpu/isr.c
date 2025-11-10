#include "isr.h"

#include <stdint.h>
#include <stdbool.h>
#include "lib/std.h"
#include "cpu/io.h"
#include "cpu/idt.h"
#include "drivers/vga.h"

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

void remap_pics()
{
	outb(0x20, 0x11);
	io_wait();
	outb(0xA0, 0x11);
	io_wait();
	outb(0x21, 0x20);
	io_wait();
	outb(0xA1, 0x28);
	io_wait();
	outb(0x21, 0x04);
	io_wait();
	outb(0xA1, 0x02);
	io_wait();
	outb(0x21, 0x01);
	io_wait();
	outb(0xA1, 0x01);
	io_wait();
	outb(0x21, 0x00);
	io_wait();
	outb(0xA1, 0x00);
	io_wait();
}

void irq_mask(uint8_t irq_line, bool masking) {
	uint16_t pic_port = 0x21;
	if (irq_line >= 8) {
		pic_port = 0xA1;
		irq_line -= 8;
	}

	uint8_t mask = inb(pic_port);
	if (masking) {
		mask &= ~(1 << irq_line);
	} else {
		mask |= 1 << irq_line;
	}

	outb(pic_port, mask);
}

void isr_common(stack_frame_t frame)
{
	uint32_t id = frame.int_num;
	if (id >= 32 && id < 48)
	{
		if (id >= 40) outb(0xA0, 0x20);
		outb(0x20, 0x20);
	}
	isr_handlers[id](frame);
}

static void default_handler(stack_frame_t frame) {
	uint32_t id = frame.int_num;
	char buffer[5];
	puts("[int 0x");
	puts(itoa(id, buffer, 16));
	putc(' ');
	if (id < 48) {
		puts(exceptions[id]);
		if (id >= 32) puts(" IRQ");
	}
	puts("] Not handled\n");
}

isr_handler_t isr_handlers[256] = {[0 ... 255] = default_handler};

void isr_init()
{
	for (int i = 0; i < 256; i++)
	{
		idt_set_gate(i, stub_table[i]);
	}
	remap_pics();
}
