#ifndef IO_H
#define IO_H

#include <stdint.h>

namespace io {

template <typename T, typename P> T in(P port) {
	T data;
	asm volatile("in%z0 %1, %0" : "=a"(data) : "Nd"(static_cast<uint16_t>(port)));
	return data;
}

template <typename T, typename P> void out(P port, T data) {
	asm volatile("out%z0 %0, %1" : : "a"(data), "Nd"(static_cast<uint16_t>(port)));
}

} // namespace io

#endif // IO_H
