# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /opt/cmake-3.21.0-rc1-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.21.0-rc1-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/admin/Documents/Code/arp_injection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/admin/Documents/Code/arp_injection/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/arp_injection.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/arp_injection.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/arp_injection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/arp_injection.dir/flags.make

CMakeFiles/arp_injection.dir/main.cpp.o: CMakeFiles/arp_injection.dir/flags.make
CMakeFiles/arp_injection.dir/main.cpp.o: ../main.cpp
CMakeFiles/arp_injection.dir/main.cpp.o: CMakeFiles/arp_injection.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/admin/Documents/Code/arp_injection/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/arp_injection.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/arp_injection.dir/main.cpp.o -MF CMakeFiles/arp_injection.dir/main.cpp.o.d -o CMakeFiles/arp_injection.dir/main.cpp.o -c /home/admin/Documents/Code/arp_injection/main.cpp

CMakeFiles/arp_injection.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arp_injection.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/admin/Documents/Code/arp_injection/main.cpp > CMakeFiles/arp_injection.dir/main.cpp.i

CMakeFiles/arp_injection.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arp_injection.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/admin/Documents/Code/arp_injection/main.cpp -o CMakeFiles/arp_injection.dir/main.cpp.s

# Object files for target arp_injection
arp_injection_OBJECTS = \
"CMakeFiles/arp_injection.dir/main.cpp.o"

# External object files for target arp_injection
arp_injection_EXTERNAL_OBJECTS =

arp_injection: CMakeFiles/arp_injection.dir/main.cpp.o
arp_injection: CMakeFiles/arp_injection.dir/build.make
arp_injection: CMakeFiles/arp_injection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/admin/Documents/Code/arp_injection/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable arp_injection"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arp_injection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/arp_injection.dir/build: arp_injection
.PHONY : CMakeFiles/arp_injection.dir/build

CMakeFiles/arp_injection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/arp_injection.dir/cmake_clean.cmake
.PHONY : CMakeFiles/arp_injection.dir/clean

CMakeFiles/arp_injection.dir/depend:
	cd /home/admin/Documents/Code/arp_injection/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/admin/Documents/Code/arp_injection /home/admin/Documents/Code/arp_injection /home/admin/Documents/Code/arp_injection/cmake-build-debug /home/admin/Documents/Code/arp_injection/cmake-build-debug /home/admin/Documents/Code/arp_injection/cmake-build-debug/CMakeFiles/arp_injection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/arp_injection.dir/depend

