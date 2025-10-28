#ifndef ISR_H
#define ISR_H

#include <cstdint>

namespace isr {


struct frame_t {
	uint32_t ds; /* we pushed this */
	uint32_t edi, esi, ebp, esp_new, ebx, edx, ecx, eax; /* pusha */
	uint32_t int_num, error_code; /* have to push manually */
	uint32_t eip, cs, eflags, esp, ss; /* cpu pushes for interrupt */
} __attribute__((packed));

extern "C" uint32_t stub_table[];

void init_default();
extern "C" void default_handler(frame_t frame);


} /* namespace isr */

#endif /* ISR_H */
