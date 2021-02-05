#include <stdint.h>

uint16_t satsum(uint16_t x, uint16_t y) {
    uint16_t result = x + y;
    if (result < x || result < y) {
        return (uint16_t) (~0);
    }
    return result;
}
