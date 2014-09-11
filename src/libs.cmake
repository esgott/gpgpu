find_library(OPENGL_GL_LIB NAMES GL)
find_library(OPENGL_GLU_LIB NAMES GLU)
find_library(GLUT_LIB glut)
find_library(GLEW_LIB GLEW)
find_library(NVIDIA_CG_LIB NAMES Cg)
find_library(NVIDIA_CGGL_LIB NAMES CgGL)

set(UBUNTU_TRUSTY_PACKAGES "libglu1-mesa-dev libglew-dev freeglut3-dev libdevil-dev nvidia-cg-dev")

if (${OPENGL_GL_LIB} STREQUAL "OPENGL_GL_LIB-NOTFOUND" OR
    ${OPENGL_GLU_LIB} STREQUAL "OPENGL_GLU_LIB-NOTFOUND" OR
    ${GLUT_LIB} STREQUAL "GLUT_LIB-NOTFOUND" OR
    ${GLEW_LIB} STREQUAL "GLW_LIB-NOTFOUND" OR
    ${NVIDIA_CG_LIB} STREQUAL "NVIDIA_CG_LIB-NOTFOUND" OR
    ${NVIDIA_CGGL_LIB} STREQUAL "NVIDIA_CGGL_LIB-NOTFOUND"
   )
    message(FATAL_ERROR "Some packages may not be installed (try e.g. sudo apt-get install ${UBUNTU_TRUSTY_PACKAGES})")
endif()
