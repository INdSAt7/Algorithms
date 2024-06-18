cmake_minimum_required(VERSION 3.26)
project(Part2_new_)

set(CMAKE_CXX_STANDARD 17)

add_executable(Part2_new_ main.cpp
        matrix.cpp
        matrix.h
        matrix_sum_krm.cpp
        matrix_sum_krm.h
        matrix_mul_krm.cpp)
