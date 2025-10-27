#ifndef IDT_H
#define IDT_H

#include <cstdint>

namespace idt {

inline constexpr int CS = 0x08;

struct descriptor_t {
	uint16_t size;
	uint32_t offset;
} __attribute__((packed));

struct gate_t {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t : 8; /* reserved */
	uint8_t flags;
	uint16_t offset_high;
} __attribute__((packed));

extern gate_t idt[256];

void set_gate(int n, uint32_t handler);
void lidt(descriptor_t* descriptor);

} /* namespace idt */

#endif /* IDT_H */
