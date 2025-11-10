#include <stdint.h>
#include <stdbool.h>
#include "drivers/vga.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/timer.h"
#include "cpu/io.h"
#include "lib/std.h"
#include "drivers/pci.h"

static void tone(uint32_t nFrequence) {
	uint32_t Div;
	uint8_t tmp;

	Div = 1193180 / nFrequence;
	outb(0x43, 0xb6);
	outb(0x42, (uint8_t) (Div) );
	outb(0x42, (uint8_t) (Div >> 8));

	tmp = inb(0x61);
	if (tmp != (tmp | 3)) {
		outb(0x61, tmp | 3);
	}
}

static void shut_up() {
	uint8_t tmp = inb(0x61) & 0xFC;
	outb(0x61, tmp);
}

uint8_t bus = 0, device = 0, function = 0;
uint8_t update_count() {
	function++;
	if (function == 0) {
		device++;
		if (device == 0) {
			bus++;
			if (bus == 0) {
				puts("Back to 0!\n\n");
				return 1;
			}
		}
	}
	return 0;
}

void on_keyboard(stack_frame_t frame) {
	if (inb(0x60) > 57) return;
	while (pci_read(bus, device, function, 0) == 0xFFFF) {
		if (update_count() == 1) break;
	}

	char buf[11];
	puts("Bus ");
	puts(itoa(bus, buf, 10));
	puts(", device ");
	puts(itoa(device, buf, 10));
	puts(", function ");
	puts(itoa(function, buf, 10));
	puts(": ");
	for (int reg = 0; reg < 256; reg += 2) {
		puts(itoa(pci_read(bus, device, function, reg), buf, 16));
		putc(' ');
	}
	puts("\n\n");
	update_count();
}

void kmain()
{
	vga_default_color = (vga_attribute_t){light_green, black};
//	vga_clear(vga_default_color);
	puts("Hello, world!\n");

	idt_descriptor_t desc = {sizeof(idt) - 1, (uint32_t)&idt};

	isr_init();
	lidt(&desc);
	timer_init(1193);
	isr_handlers[33] = on_keyboard;
	irq_mask(11, true);
	asm("sti");

	puts("\x02 Finished IDT setup!\n");
	tone(880);
	sleep(75);
	tone(1397);
	sleep(75);
	shut_up();

	puts("Press any key to scroll PCI devices\n");

}
