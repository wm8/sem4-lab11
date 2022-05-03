cmake_minimum_required(VERSION 3.18)
set( CMAKE_CXX_COMPILER "/usr/bin/g++" )
set( CMAKE_C_COMPILER "/usr/bin/gcc" )

project(sem4_RK1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_COVERAGE "Build code coverage" OFF)

add_executable(sem4_RK1 main.cpp)
