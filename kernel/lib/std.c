#include "std.h"

#include <stdint.h>
#include <stdbool.h>

static void reverse(char* str, int length) {
    char* end = str + length - 1;
    while (str < end) {
        char temp = *str;
        *str = *end;
        *end = temp;
        str++;
        end--;
    }
}

char* itoa(int value, char* buffer, uint8_t base) {
    int32_t i = 0;

    if (value == 0 || base < 2 || base > 36) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer;
    }

    bool negative = (value < 0) && (base == 10);
    if (negative) {
        value = -value;
    }

    while (value != 0) {
        int32_t remainder = value % base;
        value = value / base;
        if (remainder > 9) {
            buffer[i++] = 'a' + (remainder - 10);
        } else {
            buffer[i++] = '0' + remainder;
        }
    }

    if (negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    reverse(buffer, i);

    return buffer;
}