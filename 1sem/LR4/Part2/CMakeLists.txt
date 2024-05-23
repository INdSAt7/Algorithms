cmake_minimum_required(VERSION 3.26)
project(Part2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Part2 main.cpp
        matrix_sum_krm.cpp
        matrix.cpp
        matrix_mul_krm.cpp)
