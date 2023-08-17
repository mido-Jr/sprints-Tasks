#!/bin/bash

gcc -fPIC -shared mathlib.c -o libmathlib.so

gcc -o test_shared main.c -L. -lmathlib -lm

