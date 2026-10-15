include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(OpenMP)

add_library(renderlib
Camera.h Camera.cpp
Color.h
Framebuffer.h Framebuffer.cpp
PointLight.h
Ray.h
Scene.h Scene.cpp
Vec3.h
Shader.h
SolidShader.h
LambertianShader.h
BlinnPhongShader.h
Shape.h
Sphere.h Sphere.cpp
Triangle.h Triangle.cpp
)

# target_link_libraries(renderlib PUBLIC PNG::PNG)
# target_link_libraries(renderlib PUBLIC ZLIB::ZLIB)

add_executable(main main.cpp)
add_executable(tmp tmp.cpp)


target_link_libraries(main renderlib)
target_link_libraries(main cs4212-util)
target_link_libraries(main PNG::PNG)
if (OpenMP_CXX_FOUND)
  target_link_libraries(renderlib PRIVATE OpenMP::OpenMP_CXX)
endif()

target_link_libraries(tmp renderlib)
target_link_libraries(tmp cs4212-util)
target_link_libraries(tmp PNG::PNG)
