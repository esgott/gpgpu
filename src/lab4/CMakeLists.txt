add_executable(lab4 main.cpp)

target_link_libraries(lab4
    framebuffer
    pointgrid
    quad
    shader
    texture
    ${OPENGL_GL_LIB}
    ${GLUT_LIB}
    ${GLEW_LIB}
    ${DEVIL_IL_LIB}
    ${DEVIL_ILU_LIB}
    )
