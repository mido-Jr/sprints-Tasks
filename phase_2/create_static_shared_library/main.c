// main.c
#include <stdio.h>
#include "mathlib.h"

int main() {
    int32_t a = 10, b = 5;
    
    printf("Addition: %ld\n", add(a, b));
    printf("Subtraction: %d\n", sub(a, b));
    printf("Multiplication: %ld\n", mul(a, b));
    printf("Square Root: %d\n", sqrt_int(64));

    return 0;
}
