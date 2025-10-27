#include "idt.h"

#include <cstdint>
#include "cpu/isr.h"

namespace idt {

gate_t idt[256];

void set_gate(int n, void (*handler)(void)) {
	int address = reinterpret_cast<uint32_t>(&handler);
	idt[n].offset_low = (uint16_t)(address & 0xFFFF);
	idt[n].selector = CS;
	idt[n].flags = 0b10001110;
	idt[n].offset_high = (uint16_t)(address >> 16);
}

void lidt(descriptor_t* descriptor) {
	__asm__ volatile("lidtl (%0)" : : "r" (descriptor));
}


} /* namespace idt */
