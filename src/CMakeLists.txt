cmake_minimum_required(VERSION 2.8.12)

project(gpgpu)

include(libs.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(common)
add_subdirectory(lab1_cg_opengl)
