#include <iostream> // For std::cout and std::endl
#include <string>   // For std::string
#include "Print.h"  // Your custom header
#include "WriteInFile.h" // Your custom header

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [-c/-f]" << std::endl;
        return 1;
    }

    Print printer;

    if (std::string(argv[1]) == "-c") {
        printer.helloWorld();
    } else if (std::string(argv[1]) == "-f") {
        WriteInFile writer;
        writer.write("helloWorld.txt", "Hello, World!\n");
    } else {
        std::cout << "Invalid option: " << argv[1] << std::endl;
        return 1;
    }

    return 0;
}

