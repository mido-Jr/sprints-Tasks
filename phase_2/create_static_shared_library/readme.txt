Building the Library and Test Application:
------------------------------------------
Follow these steps to build the library and test application:

1. **Build the Static Library:**
    ```bash
    gcc -c mathlib.c -o mathlib.o
    ar rcs libmathlib.a mathlib.o
    ```

2. **Build the Shared Library:**
    ```bash
    gcc -fPIC -shared mathlib.c -o libmathlib.so -lm
    ```

3. **Build the Test Application:**
    For the static library:
    ```bash
    gcc -o test_static main.c -L. -lmathlib -lm
    ```

    For the shared library:
    ```bash
    gcc -o test_shared main.c -L. -lmathlib -lm
    ```

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
./test_shared