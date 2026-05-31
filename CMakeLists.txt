cmake_minimum_required(VERSION 3.16)
project(Aion)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)

# GLAD
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(Aion
    src/main.cpp
    src/stb_image.cpp
    
    src/Aion/Core/Application.cpp
    src/Aion/Assets/Mesh.cpp
    src/Aion/Assets/Model.cpp
    src/Aion/Renderer/Camera.cpp
    src/Aion/Renderer/Material.cpp
	src/Aion/Renderer/Renderer.cpp
	src/Aion/Renderer/Shader.cpp
    src/Aion/Renderer/Texture.cpp

    src/Aion/Scene/Transform.cpp
)

target_include_directories(Aion PRIVATE
    external/glfw/include
    external/glad/include
    external/glm
    external/json
    external/stb
    external/tinygltf
    external
    src
)

target_link_libraries(Aion glfw glad opengl32)

# =========================================
# Copy Assets Folder
# =========================================

add_custom_command(
    TARGET Aion POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Aion>/assets
)