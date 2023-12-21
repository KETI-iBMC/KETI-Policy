set(
    OUTPUT
    Policy
)
set(
    SOURCE_FILES
    policy.cpp
    main.cpp
    )

add_executable(${OUTPUT} ${SOURCE_FILES})

target_link_libraries( ${OUTPUT}
libdbus-c++-1.so.0

)