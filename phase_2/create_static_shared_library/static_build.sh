#!/bin/bash

gcc -c mathlib.c -o mathlib.o
ar rcs libmathlib.a mathlib.o
gcc -o test_static main.c -L. -lmathlib -lm
