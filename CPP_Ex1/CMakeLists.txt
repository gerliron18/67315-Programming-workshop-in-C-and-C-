cmake_minimum_required(VERSION 3.15)
project(CPP_Ex1)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP_Ex1 main.cpp Matrix.cpp Activation.cpp Dense.cpp Dense.h  Digit.h MlpNetwork.cpp)