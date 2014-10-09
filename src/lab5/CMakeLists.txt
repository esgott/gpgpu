add_executable(lab5 main.cpp)

target_link_libraries(lab5
    camera
    framebuffer
    matrix4x4
    quad
    shader
    ${OPENGL_GL_LIB}
    ${GLUT_LIB}
    ${GLEW_LIB}
    ${DEVIL_IL_LIB}
    ${DEVIL_ILU_LIB}
    )
