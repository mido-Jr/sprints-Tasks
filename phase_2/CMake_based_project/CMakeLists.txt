cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(include)

# Add the static library target
add_library(WriteInFile STATIC Library/WriteInFile.cpp)

# Add the executable target
add_executable(program src/main.cpp src/print.cpp)

# Link the executable with the static library
target_link_libraries(program PRIVATE WriteInFile)
