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
include CMakeFiles/product_example_mine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/product_example_mine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/product_example_mine.dir/flags.make

CMakeFiles/product_example_mine.dir/ProductExample.c.o: CMakeFiles/product_example_mine.dir/flags.make
CMakeFiles/product_example_mine.dir/ProductExample.c.o: ../ProductExample.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/product_example_mine.dir/ProductExample.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/product_example_mine.dir/ProductExample.c.o   -c "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/ProductExample.c"

CMakeFiles/product_example_mine.dir/ProductExample.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/product_example_mine.dir/ProductExample.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/ProductExample.c" > CMakeFiles/product_example_mine.dir/ProductExample.c.i

CMakeFiles/product_example_mine.dir/ProductExample.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/product_example_mine.dir/ProductExample.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/ProductExample.c" -o CMakeFiles/product_example_mine.dir/ProductExample.c.s

# Object files for target product_example_mine
product_example_mine_OBJECTS = \
"CMakeFiles/product_example_mine.dir/ProductExample.c.o"

# External object files for target product_example_mine
product_example_mine_EXTERNAL_OBJECTS =

product_example_mine.exe: CMakeFiles/product_example_mine.dir/ProductExample.c.o
product_example_mine.exe: CMakeFiles/product_example_mine.dir/build.make
product_example_mine.exe: libex3_lib.a
product_example_mine.exe: tree_visualizer/libtree_visualizer.a
product_example_mine.exe: CMakeFiles/product_example_mine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable product_example_mine.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/product_example_mine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/product_example_mine.dir/build: product_example_mine.exe

.PHONY : CMakeFiles/product_example_mine.dir/build

CMakeFiles/product_example_mine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/product_example_mine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/product_example_mine.dir/clean

CMakeFiles/product_example_mine.dir/depend:
	cd "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/CMakeFiles/product_example_mine.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/product_example_mine.dir/depend

