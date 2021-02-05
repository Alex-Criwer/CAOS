#include <stdio.h>
#include <stdint.h>

const uint64_t BASE = 1;
const uint32_t MAX_DEGREE_WITHOUT_PROBLEMS = 24;
const uint32_t MAX_NUMBER_WITHOUT_PROBLEMS =
        (BASE << MAX_DEGREE_WITHOUT_PROBLEMS);
const uint32_t MAX_DEGREE = 32;

uint32_t addOne(uint32_t number){
    uint32_t temp = 1;
    while(number & temp){
        number = number ^ temp;
        temp <<= 1;
    }
    number = number ^ temp;
    return number;
}

extern int
check_int(uint32_t u32) {
    if (u32 < MAX_NUMBER_WITHOUT_PROBLEMS) {
        return 1;
    }
    size_t i = 0;
    uint32_t divider = 1;
    for (i = MAX_DEGREE_WITHOUT_PROBLEMS; i < MAX_DEGREE; i = addOne(i)) {
        if ((u32 >= (BASE << i)) && (u32 < (BASE << (addOne(i))))) {
            if (((u32 >> divider) << divider) == u32) {
                return 1;
            } else {
                return 0;
            }
        }
        divider = addOne(divider);
    }
    return 0;
}