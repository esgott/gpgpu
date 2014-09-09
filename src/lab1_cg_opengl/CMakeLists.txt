add_executable(lab1 main.cpp)

target_link_libraries(lab1
    quad
    texture
    shader
    ${OPENGL_LIB}
    ${GLUT_LIB}
    ${GLEW_LIB}
    )
