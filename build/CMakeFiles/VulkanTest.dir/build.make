# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marc/Documents/dev/VulkanTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marc/Documents/dev/VulkanTest/build

# Include any dependencies generated for this target.
include CMakeFiles/VulkanTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VulkanTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VulkanTest.dir/flags.make

CMakeFiles/VulkanTest.dir/srcs/main.cpp.o: CMakeFiles/VulkanTest.dir/flags.make
CMakeFiles/VulkanTest.dir/srcs/main.cpp.o: ../srcs/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marc/Documents/dev/VulkanTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VulkanTest.dir/srcs/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VulkanTest.dir/srcs/main.cpp.o -c /home/marc/Documents/dev/VulkanTest/srcs/main.cpp

CMakeFiles/VulkanTest.dir/srcs/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VulkanTest.dir/srcs/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marc/Documents/dev/VulkanTest/srcs/main.cpp > CMakeFiles/VulkanTest.dir/srcs/main.cpp.i

CMakeFiles/VulkanTest.dir/srcs/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VulkanTest.dir/srcs/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marc/Documents/dev/VulkanTest/srcs/main.cpp -o CMakeFiles/VulkanTest.dir/srcs/main.cpp.s

CMakeFiles/VulkanTest.dir/srcs/main.cpp.o.requires:

.PHONY : CMakeFiles/VulkanTest.dir/srcs/main.cpp.o.requires

CMakeFiles/VulkanTest.dir/srcs/main.cpp.o.provides: CMakeFiles/VulkanTest.dir/srcs/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/VulkanTest.dir/build.make CMakeFiles/VulkanTest.dir/srcs/main.cpp.o.provides.build
.PHONY : CMakeFiles/VulkanTest.dir/srcs/main.cpp.o.provides

CMakeFiles/VulkanTest.dir/srcs/main.cpp.o.provides.build: CMakeFiles/VulkanTest.dir/srcs/main.cpp.o


# Object files for target VulkanTest
VulkanTest_OBJECTS = \
"CMakeFiles/VulkanTest.dir/srcs/main.cpp.o"

# External object files for target VulkanTest
VulkanTest_EXTERNAL_OBJECTS =

VulkanTest: CMakeFiles/VulkanTest.dir/srcs/main.cpp.o
VulkanTest: CMakeFiles/VulkanTest.dir/build.make
VulkanTest: CMakeFiles/VulkanTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marc/Documents/dev/VulkanTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VulkanTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VulkanTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VulkanTest.dir/build: VulkanTest

.PHONY : CMakeFiles/VulkanTest.dir/build

CMakeFiles/VulkanTest.dir/requires: CMakeFiles/VulkanTest.dir/srcs/main.cpp.o.requires

.PHONY : CMakeFiles/VulkanTest.dir/requires

CMakeFiles/VulkanTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VulkanTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VulkanTest.dir/clean

CMakeFiles/VulkanTest.dir/depend:
	cd /home/marc/Documents/dev/VulkanTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marc/Documents/dev/VulkanTest /home/marc/Documents/dev/VulkanTest /home/marc/Documents/dev/VulkanTest/build /home/marc/Documents/dev/VulkanTest/build /home/marc/Documents/dev/VulkanTest/build/CMakeFiles/VulkanTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VulkanTest.dir/depend

