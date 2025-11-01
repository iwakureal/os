#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct __attribute__((packed))
{
	uint32_t ds;										 /* we pushed this */
	uint32_t edi, esi, ebp, esp_new, ebx, edx, ecx, eax; /* pusha */
	uint32_t int_num, error_code;						 /* have to push manually */
	uint32_t eip, cs, eflags, esp, ss;					 /* cpu pushes for interrupt */
} stack_frame_t;

extern uint32_t stub_table[];

void isr_init();

#endif /* ISR_H */
