cmake_minimum_required(VERSION 2.8.12)

project(gpgpu)

include(libs.cmake)
include(symlink.cmake)

include_directories(common)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(common)
add_subdirectory(lab1_cg_opengl)
add_subdirectory(lab2)
add_subdirectory(lab3)
add_subdirectory(lab4)
add_subdirectory(lab5)
add_subdirectory(lab6_recursive)
add_subdirectory(lab8)
add_subdirectory(lab9)
add_subdirectory(lab10)
