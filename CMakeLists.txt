cmake_minimum_required(VERSION 3.16)

project(Aion)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==================================================
# Dependencies
# ==================================================

add_subdirectory(external/glfw)

add_library(glad
    external/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    external/glad/include
)

# ==================================================
# Engine Library
# ==================================================

file(GLOB_RECURSE AION_SOURCES
    src/Aion/*.cpp
)

add_library(AionEngine
    ${AION_SOURCES}
    src/stb_image.cpp
)

target_include_directories(AionEngine PUBLIC

    src

    external/glad/include
    external/glfw/include

    external/glm
    external/json
    external/stb
    external/tinygltf
    external
)

target_link_libraries(
    AionEngine
    PUBLIC
    glfw
    glad
    opengl32
)

# ==================================================
# Sandbox
# ==================================================

add_executable(Sandbox

    Sandbox/Main.cpp
    Sandbox/Application.cpp
)

target_link_libraries(
    Sandbox
    PRIVATE
    AionEngine
)

# ==================================================
# Copy Assets
# ==================================================

add_custom_command(
    TARGET Sandbox POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Sandbox>/assets
)