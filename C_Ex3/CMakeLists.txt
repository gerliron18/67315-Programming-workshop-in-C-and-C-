cmake_minimum_required(VERSION 3.15)
project(C_Ex3 C)

set(CMAKE_C_STANDARD 99)

add_library(RBTree.h RBTree.c)
add_library(Structs.h Structs.c)
add_executable(C_Ex3 RBTree.c Structs.c ProductExample.c)