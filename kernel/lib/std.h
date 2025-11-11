#ifndef STD_H
#define STD_H

#include <stdint.h>
#include <stddef.h>

char* reverse(char* str, int length);
char* itoa(int value, char* buffer, uint8_t base);

inline void stosb(void *dest, uint8_t value, size_t n) {
	asm volatile(
		"cld;"
		"rep stosb;"
		: "+D" (dest),
		  "+c" (n)
		: "a" (value)
		: "memory"
	);
}

inline void stosw(void *dest, uint16_t value, size_t n) {
	asm volatile(
		"cld;"
		"rep stosw;"
		: "+D" (dest),
		  "+c" (n)
		: "a" (value)
		: "memory"
	);
}

inline void movsb(void *dest, const void *src, size_t n) {
	asm volatile(
		"cld;"
		"rep movsb;"
		: "+D" (dest),
		  "+S" (src),
		  "+c" (n)
		:
		: "memory"
	);
}

#endif
