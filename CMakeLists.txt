cmake_minimum_required(VERSION 3.16)
project(Aion)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(Aion
    src/main.cpp
    src/Aion/Core/Application.cpp
    src/Aion/Renderer/Camera.cpp
	src/Aion/Renderer/Renderer.cpp
	src/Aion/Renderer/Shader.cpp
)

target_include_directories(Aion PRIVATE
    external/glfw/include
    external/glad/include
    external/glm
    src
)

target_link_libraries(Aion glfw glad opengl32)