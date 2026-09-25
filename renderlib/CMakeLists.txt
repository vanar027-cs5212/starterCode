include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(renderlib
Camera.cpp Camera.h
Color.h
Framebuffer.cpp Framebuffer.h
Ray.h
Scene.h
Shader.cpp Shader.h
Shape.h
Sphere.cpp Sphere.h
Triangle.cpp Triangle.h
Vec3.h
)

# target_link_libraries(renderlib PUBLIC PNG::PNG)
# target_link_libraries(renderlib PUBLIC ZLIB::ZLIB)

add_executable(main main.cpp)


target_link_libraries(main renderlib)
target_link_libraries(main cs4212-util)
target_link_libraries(main PNG::PNG)