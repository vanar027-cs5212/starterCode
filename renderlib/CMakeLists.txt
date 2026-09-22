include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(renderlib
Camera.cpp
Camera.h
color.h
Framebuffer.cpp
Framebuffer.h
ray.h
vec3.h
)

# target_link_libraries(renderlib PUBLIC PNG::PNG)
# target_link_libraries(renderlib PUBLIC ZLIB::ZLIB)

add_executable(main main.cpp)


target_link_libraries(main renderlib)
target_link_libraries(main cs4212-util)
target_link_libraries(main PNG::PNG)