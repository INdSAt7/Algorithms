cmake_minimum_required(VERSION 3.26)
project(RK3)

set(CMAKE_CXX_STANDARD 17)

add_executable(RK3 main.cpp
        dfs.h
        bfs.h
        node.h
        queue.h
        stack.h)
