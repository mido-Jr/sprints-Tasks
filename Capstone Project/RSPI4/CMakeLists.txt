cmake_minimum_required(VERSION 3.10)
project(LoggerDaemon)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)  # or 14, 17, etc.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Specify the compiler (Optional, only if you want to enforce a specific compiler)
# set(CMAKE_CXX_COMPILER g++)  # Replace with the desired compiler

 #Specify the cross-compiling toolchain
#set(CMAKE_C_COMPILER /home/mido/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-gcc)
#set(CMAKE_CXX_COMPILER /home/mido/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++)


find_package(Boost REQUIRED COMPONENTS log)


# Build the IPC library
add_library(ipc_library SHARED
    ../libraries/ipc_library.cpp
    ../libraries/ipc_library.h
)


# Build the File library
add_library(file_library
    ../libraries/file.cpp
    ../libraries/file.h
)

# Build the LoggerDaemon executable
add_executable(Daemon
    Daemon.cpp
    ../libraries/logger.cpp
)

# Build the Mathematical executable
add_executable(Mathapp
    Mathematical.cpp
    ../libraries/logger.cpp
)

# Link libraries
target_link_libraries(Daemon
    ipc_library
    file_library
    Boost::log
    rt
)

target_link_libraries(Mathapp
    ipc_library
    file_library
    Boost::log
    rt
)

# Include directories
target_include_directories(Daemon
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries
)

target_include_directories(Mathapp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries
)

