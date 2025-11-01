#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define CS 0x08

typedef struct __attribute__((packed))  {
	uint16_t size;
	uint32_t offset;
} idt_descriptor_t;

typedef struct  __attribute__((packed)) {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t : 8; /* reserved */
	uint8_t flags;
	uint16_t offset_high;
} idt_gate_t;

extern idt_gate_t idt[256];

void idt_set_gate(int n, uint32_t handler);
void lidt(idt_descriptor_t* descriptor);

#endif /* IDT_H */
