add_executable(lab3 main.cpp)

target_link_libraries(lab3
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
