include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(renderlib INTERFACE
    vec3.h
    color.h
)

# add_executable(mainCode mainCode.cpp)


# target_link_libraries(mainCode renderlib)
# target_link_libraries(mainCode cs4212-util)