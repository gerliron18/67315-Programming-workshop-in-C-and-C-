# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/Users/User/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/User/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug"

# Include any dependencies generated for this target.
include tree_visualizer/CMakeFiles/tree_visualizer.dir/depend.make

# Include the progress variables for this target.
include tree_visualizer/CMakeFiles/tree_visualizer.dir/progress.make

# Include the compile flags for this target's objects.
include tree_visualizer/CMakeFiles/tree_visualizer.dir/flags.make

tree_visualizer/CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.o: tree_visualizer/CMakeFiles/tree_visualizer.dir/flags.make
tree_visualizer/CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.o: ../tree_visualizer/graph_drawer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tree_visualizer/CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.o"
	cd "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/tree_visualizer" && /usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.o -c "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/tree_visualizer/graph_drawer.cpp"

tree_visualizer/CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.i"
	cd "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/tree_visualizer" && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/tree_visualizer/graph_drawer.cpp" > CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.i

tree_visualizer/CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.s"
	cd "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/tree_visualizer" && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/tree_visualizer/graph_drawer.cpp" -o CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.s

# Object files for target tree_visualizer
tree_visualizer_OBJECTS = \
"CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.o"

# External object files for target tree_visualizer
tree_visualizer_EXTERNAL_OBJECTS =

tree_visualizer/libtree_visualizer.a: tree_visualizer/CMakeFiles/tree_visualizer.dir/graph_drawer.cpp.o
tree_visualizer/libtree_visualizer.a: tree_visualizer/CMakeFiles/tree_visualizer.dir/build.make
tree_visualizer/libtree_visualizer.a: tree_visualizer/CMakeFiles/tree_visualizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtree_visualizer.a"
	cd "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/tree_visualizer" && $(CMAKE_COMMAND) -P CMakeFiles/tree_visualizer.dir/cmake_clean_target.cmake
	cd "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/tree_visualizer" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tree_visualizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tree_visualizer/CMakeFiles/tree_visualizer.dir/build: tree_visualizer/libtree_visualizer.a

.PHONY : tree_visualizer/CMakeFiles/tree_visualizer.dir/build

tree_visualizer/CMakeFiles/tree_visualizer.dir/clean:
	cd "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/tree_visualizer" && $(CMAKE_COMMAND) -P CMakeFiles/tree_visualizer.dir/cmake_clean.cmake
.PHONY : tree_visualizer/CMakeFiles/tree_visualizer.dir/clean

tree_visualizer/CMakeFiles/tree_visualizer.dir/depend:
	cd "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/tree_visualizer" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/tree_visualizer" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/tree_visualizer/CMakeFiles/tree_visualizer.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tree_visualizer/CMakeFiles/tree_visualizer.dir/depend

