add_executable(lab10
    main.cpp
    )

target_link_libraries(lab10
    clwrapper
    ${OPENCL_LIB}
    )
