#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

namespace timer {


inline constexpr uint32_t BASE_CLOCK = 1193182;

void init(volatile uint32_t freq);


} // namespace timer

#endif
