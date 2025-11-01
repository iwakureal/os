#include "idt.h"

#include <stdint.h>

idt_gate_t idt[256];

void idt_set_gate(int n, uint32_t handler) {
	idt[n].offset_low = (uint16_t)(handler & 0xFFFF);
	idt[n].selector = CS;
	idt[n].flags = 0b10001110;
	idt[n].offset_high = (uint16_t)(handler >> 16);
}

void lidt(idt_descriptor_t* descriptor) {
	asm volatile("lidt %0" : : "m" (*descriptor));
}