cmake_minimum_required(VERSION 3.18)
project(CG_HW04)

set(CMAKE_CXX_STANDARD 14)

file(GLOB CG_HW04
        "*.h"
        "*.cpp"
        )

add_executable(CG_HW04 ${CG_HW04})
#add_executable(CG_HW04 main.cpp)