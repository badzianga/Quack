cmake_minimum_required(VERSION 3.31)
project(Quack)

set(CMAKE_CXX_STANDARD 20)

add_executable(Quack main.cpp
        src/Core/Engine.cpp
        include/Core/Engine.hpp)

target_include_directories(Quack PRIVATE include)
