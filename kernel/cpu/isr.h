#ifndef ISR_H
#define ISR_H

#include <cstdint>

namespace isr {

struct frame_t {
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_num, error_code;
	uint32_t eip, cs, eflags;
} __attribute__((packed));

extern "C" uint32_t stub_table[];

void init_default();
//void default_handler(frame_t* frame);


} /* namespace isr */

#endif /* ISR_H */
