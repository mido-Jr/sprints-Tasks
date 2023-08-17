// mathlib.c
#include <math.h>
#include "mathlib.h"
#include <stdint.h>
int64_t add(int32_t a, int32_t b) {
    return (int64_t)a + b;
}

int32_t sub(int32_t a, int32_t b) {
    return a - b;
}

int64_t mul(int32_t a, int32_t b) {
    return (int64_t)a * b;
}

int32_t sqrt_int(int64_t x) {
    return (int32_t)sqrt((double)x);
}
