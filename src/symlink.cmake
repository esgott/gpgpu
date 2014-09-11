add_custom_command(
    OUTPUT
        lab1.cg
    COMMAND
        ln -sf ${CMAKE_CURRENT_SOURCE_DIR}/lab1_cg_opengl/lab1.cg lab1.cg
    )

add_custom_target(
    generate_symlinks
    DEPENDS
        lab1.cg
    )
