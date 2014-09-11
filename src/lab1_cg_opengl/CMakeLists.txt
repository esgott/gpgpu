add_executable(lab1 main.cpp)

target_link_libraries(lab1
    ${OPENGL_GL_LIB}
    ${OPENGL_GLU_LIB}
    ${GLUT_LIB}
    ${GLEW_LIB}
    ${NVIDIA_CG_LIB}
    ${NVIDIA_CGGL_LIB}
    )

add_dependencies(lab1 generate_symlinks)
