add_executable(lab8
    main.cpp
    clwrapper.cpp
    )

target_link_libraries(lab8
    ${OPENCL_LIB}
    )
