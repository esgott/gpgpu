add_executable(lab8
    main.cpp
    )

target_link_libraries(lab8
    clwrapper
    ${OPENCL_LIB}
    )
