#ifndef ISR_H
#define ISR_H

#include <cstdint>

namespace isr {

struct frame_t {
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
};

void init_default();
void default_handler(frame_t* frame);


} /* namespace isr */

#endif /* ISR_H */
