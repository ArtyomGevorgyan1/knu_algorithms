# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /opt/clion-2018.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.3.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/artyom/Documents/algos/knu_algorithms/b+_tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/artyom/Documents/algos/knu_algorithms/b+_tree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/b__tree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/b__tree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/b__tree.dir/flags.make

CMakeFiles/b__tree.dir/main.cpp.o: CMakeFiles/b__tree.dir/flags.make
CMakeFiles/b__tree.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artyom/Documents/algos/knu_algorithms/b+_tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/b__tree.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/b__tree.dir/main.cpp.o -c /home/artyom/Documents/algos/knu_algorithms/b+_tree/main.cpp

CMakeFiles/b__tree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/b__tree.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/artyom/Documents/algos/knu_algorithms/b+_tree/main.cpp > CMakeFiles/b__tree.dir/main.cpp.i

CMakeFiles/b__tree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/b__tree.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/artyom/Documents/algos/knu_algorithms/b+_tree/main.cpp -o CMakeFiles/b__tree.dir/main.cpp.s

# Object files for target b__tree
b__tree_OBJECTS = \
"CMakeFiles/b__tree.dir/main.cpp.o"

# External object files for target b__tree
b__tree_EXTERNAL_OBJECTS =

b__tree: CMakeFiles/b__tree.dir/main.cpp.o
b__tree: CMakeFiles/b__tree.dir/build.make
b__tree: CMakeFiles/b__tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/artyom/Documents/algos/knu_algorithms/b+_tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable b__tree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/b__tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/b__tree.dir/build: b__tree

.PHONY : CMakeFiles/b__tree.dir/build

CMakeFiles/b__tree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/b__tree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/b__tree.dir/clean

CMakeFiles/b__tree.dir/depend:
	cd /home/artyom/Documents/algos/knu_algorithms/b+_tree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/artyom/Documents/algos/knu_algorithms/b+_tree /home/artyom/Documents/algos/knu_algorithms/b+_tree /home/artyom/Documents/algos/knu_algorithms/b+_tree/cmake-build-debug /home/artyom/Documents/algos/knu_algorithms/b+_tree/cmake-build-debug /home/artyom/Documents/algos/knu_algorithms/b+_tree/cmake-build-debug/CMakeFiles/b__tree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/b__tree.dir/depend

