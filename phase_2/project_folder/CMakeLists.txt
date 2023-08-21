cmake_minimum_required(VERSION 3.10)

project(FileHandlerApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS log)

add_subdirectory(src)
add_subdirectory(tests)
