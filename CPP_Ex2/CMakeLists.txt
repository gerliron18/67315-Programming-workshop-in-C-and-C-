cmake_minimum_required(VERSION 3.15)
project(CPP_Ex2)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "C:\\boost_1_69_0")
FIND_PACKAGE(Boost REQUIRED)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

add_executable(CPP_Ex2 FractalDrawer.cpp Fractal.h Fractal.cpp)
