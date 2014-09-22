add_executable(lab2 main.cpp)

target_link_libraries(lab2
    framebuffer
    quad
    shader
    texture
    ${OPENGL_GL_LIB}
    ${GLUT_LIB}
    ${GLEW_LIB}
    ${DEVIL_IL_LIB}
    ${DEVIL_ILU_LIB}
    )