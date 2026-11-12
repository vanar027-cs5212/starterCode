include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (glfwExample
  glfwExample.cpp
  GLSL.cpp GLSL.h
)

target_link_libraries (glfwExample PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwExample PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample PRIVATE PNG::PNG)
target_link_libraries (glfwExample PRIVATE ZLIB::ZLIB)

# Copy the entire shaders directory to the executable's output directory on every build
add_custom_command(
    TARGET glfwExample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:glfwExample>/shaders"
    COMMENT "Copying GLSL shaders to build directory..."
)
