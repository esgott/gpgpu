cmake_minimum_required(VERSION 2.8.12)

project(gpgpu)

find_library(OPENGL_LIB NAMES GL GLU)
find_library(GLUT_LIB glut)
find_library(GLEW_LIB GLEW)

set(UBUNTU_TRUSTY_PACKAGES "libglu1-mesa-dev libglew-dev freeglut3-dev libdevil-dev")

if(${OPENGL_LIB} STREQUAL "OPENGL_LIB-NOTFOUND" OR
   ${GLUT_LIB} STREQUAL "GLUT_LIB-NOTFOUND" OR
   ${GLEW_LIB} STREQUAL "GLW_LIB-NOTFOUND")
    message(FATAL_ERROR "Some packages may not be installed (try e.g. apt-get install ${UBUNTU_TRUSTY_PACKAGES})")
endif()

add_subdirectory(common)
add_subdirectory(lab1_cg_opengl)
