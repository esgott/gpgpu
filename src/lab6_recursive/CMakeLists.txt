add_executable(lab6
    main.cpp
    GraphRenderer.cpp
    )

target_link_libraries(lab6
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
