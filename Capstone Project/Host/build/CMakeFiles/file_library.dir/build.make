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
include CMakeFiles/file_library.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/file_library.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/file_library.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/file_library.dir/flags.make

CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.o: CMakeFiles/file_library.dir/flags.make
CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.o: /home/mido/valeo/Capstone\ Project/libraries/file.cpp
CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.o: CMakeFiles/file_library.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/mido/valeo/Capstone Project/Host/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.o -MF CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.o.d -o CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.o -c "/home/mido/valeo/Capstone Project/libraries/file.cpp"

CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/mido/valeo/Capstone Project/libraries/file.cpp" > CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.i

CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/mido/valeo/Capstone Project/libraries/file.cpp" -o CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.s

# Object files for target file_library
file_library_OBJECTS = \
"CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.o"

# External object files for target file_library
file_library_EXTERNAL_OBJECTS =

libfile_library.a: CMakeFiles/file_library.dir/home/mido/valeo/Capstone_Project/libraries/file.cpp.o
libfile_library.a: CMakeFiles/file_library.dir/build.make
libfile_library.a: CMakeFiles/file_library.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/mido/valeo/Capstone Project/Host/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libfile_library.a"
	$(CMAKE_COMMAND) -P CMakeFiles/file_library.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/file_library.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/file_library.dir/build: libfile_library.a
.PHONY : CMakeFiles/file_library.dir/build

CMakeFiles/file_library.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/file_library.dir/cmake_clean.cmake
.PHONY : CMakeFiles/file_library.dir/clean

CMakeFiles/file_library.dir/depend:
	cd "/home/mido/valeo/Capstone Project/Host/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/mido/valeo/Capstone Project/Host" "/home/mido/valeo/Capstone Project/Host" "/home/mido/valeo/Capstone Project/Host/build" "/home/mido/valeo/Capstone Project/Host/build" "/home/mido/valeo/Capstone Project/Host/build/CMakeFiles/file_library.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/file_library.dir/depend
