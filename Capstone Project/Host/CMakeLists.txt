project(LogServerApp)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Build the File library
add_library(file_library
    ../libraries/file.cpp
    ../libraries/file.h
)

# Build the LoggerDaemon executable
add_executable(LogServerApp
    Logger_receiver.cpp
)

# Link libraries
target_link_libraries(LogServerApp
    PRIVATE
    file_library
)

# Include directories
target_include_directories(LogServerApp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries
)

