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
include CMakeFiles/RBTree.h.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RBTree.h.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RBTree.h.dir/flags.make

CMakeFiles/RBTree.h.dir/RBTree.c.o: CMakeFiles/RBTree.h.dir/flags.make
CMakeFiles/RBTree.h.dir/RBTree.c.o: ../RBTree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RBTree.h.dir/RBTree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/RBTree.h.dir/RBTree.c.o   -c "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/RBTree.c"

CMakeFiles/RBTree.h.dir/RBTree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RBTree.h.dir/RBTree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/RBTree.c" > CMakeFiles/RBTree.h.dir/RBTree.c.i

CMakeFiles/RBTree.h.dir/RBTree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RBTree.h.dir/RBTree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/RBTree.c" -o CMakeFiles/RBTree.h.dir/RBTree.c.s

# Object files for target RBTree.h
RBTree_h_OBJECTS = \
"CMakeFiles/RBTree.h.dir/RBTree.c.o"

# External object files for target RBTree.h
RBTree_h_EXTERNAL_OBJECTS =

libRBTree.h.a: CMakeFiles/RBTree.h.dir/RBTree.c.o
libRBTree.h.a: CMakeFiles/RBTree.h.dir/build.make
libRBTree.h.a: CMakeFiles/RBTree.h.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libRBTree.h.a"
	$(CMAKE_COMMAND) -P CMakeFiles/RBTree.h.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RBTree.h.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RBTree.h.dir/build: libRBTree.h.a

.PHONY : CMakeFiles/RBTree.h.dir/build

CMakeFiles/RBTree.h.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RBTree.h.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RBTree.h.dir/clean

CMakeFiles/RBTree.h.dir/depend:
	cd "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug" "/cygdrive/c/Users/User/Documents/Computitional Biology/Year3/Semester A/Programming workshop in C and C++/Exercises/C_Ex3/cmake-build-debug/CMakeFiles/RBTree.h.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/RBTree.h.dir/depend

