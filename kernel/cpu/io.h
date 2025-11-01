#ifndef IO_H
#define IO_H

#include <stdint.h>

inline void outb(uint16_t port, uint8_t data)
{
    asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

inline void outw(uint16_t port, uint16_t data)
{
    asm volatile("outw %0, %1" : : "a"(data), "Nd"(port));
}

inline void outl(uint16_t port, uint32_t data)
{
    asm volatile("outl %0, %1" : : "a"(data), "Nd"(port));
}

inline uint8_t inb(uint16_t port)
{
    uint8_t data;
    asm volatile("inb %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

inline uint16_t inw(uint16_t port)
{
    uint16_t data;
    asm volatile("inw %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

inline uint32_t inl(uint16_t port)
{
    uint32_t data;
    asm volatile("inl %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

inline void io_wait(void)
{
    outb(0x80, 0);
}

#endif // IO_H
