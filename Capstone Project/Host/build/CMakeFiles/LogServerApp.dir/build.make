# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/mido/valeo/Capstone Project/Host"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/mido/valeo/Capstone Project/Host/build"

# Include any dependencies generated for this target.
include CMakeFiles/LogServerApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LogServerApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LogServerApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LogServerApp.dir/flags.make

CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.o: CMakeFiles/LogServerApp.dir/flags.make
CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.o: ../Logger_receiver.cpp
CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.o: CMakeFiles/LogServerApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mido/valeo/Capstone Project/Host/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.o -MF CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.o.d -o CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.o -c "/home/mido/valeo/Capstone Project/Host/Logger_receiver.cpp"

CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/mido/valeo/Capstone Project/Host/Logger_receiver.cpp" > CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.i

CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/mido/valeo/Capstone Project/Host/Logger_receiver.cpp" -o CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.s

# Object files for target LogServerApp
LogServerApp_OBJECTS = \
"CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.o"

# External object files for target LogServerApp
LogServerApp_EXTERNAL_OBJECTS =

LogServerApp: CMakeFiles/LogServerApp.dir/Logger_receiver.cpp.o
LogServerApp: CMakeFiles/LogServerApp.dir/build.make
LogServerApp: libfile_library.a
LogServerApp: CMakeFiles/LogServerApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/mido/valeo/Capstone Project/Host/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LogServerApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LogServerApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LogServerApp.dir/build: LogServerApp
.PHONY : CMakeFiles/LogServerApp.dir/build

CMakeFiles/LogServerApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LogServerApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LogServerApp.dir/clean

CMakeFiles/LogServerApp.dir/depend:
	cd "/home/mido/valeo/Capstone Project/Host/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/mido/valeo/Capstone Project/Host" "/home/mido/valeo/Capstone Project/Host" "/home/mido/valeo/Capstone Project/Host/build" "/home/mido/valeo/Capstone Project/Host/build" "/home/mido/valeo/Capstone Project/Host/build/CMakeFiles/LogServerApp.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/LogServerApp.dir/depend
