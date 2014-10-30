add_executable(lab9
    main.cpp
    )

target_link_libraries(lab9
    clwrapper
    ${OPENCL_LIB}
    )