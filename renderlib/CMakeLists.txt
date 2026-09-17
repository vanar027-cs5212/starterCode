include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(renderlib
    vec3.h
    color.h
    ray.h
    Framebuffer.h
    Framebuffer.cpp
    Camera.h
    Camera.cpp
)

add_executable(main main.cpp)


target_link_libraries(main renderlib)
target_link_libraries(main cs4212-util)
target_link_libraries(main PNG::PNG)