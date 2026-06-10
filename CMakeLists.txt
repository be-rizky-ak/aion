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

file(GLOB_RECURSE AION_HEADERS
    src/Aion/*.h
)

add_library(AionEngine
    ${AION_SOURCES}
    ${AION_HEADERS}
    src/stb_image.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    FILES
        ${AION_SOURCES}
        ${AION_HEADERS}
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

file(GLOB_RECURSE SANDBOX_SOURCES
    Sandbox/*.cpp
)

file(GLOB_RECURSE SANDBOX_HEADERS
    Sandbox/*.h
)

add_executable(Sandbox
    ${SANDBOX_SOURCES}
    ${SANDBOX_HEADERS}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox
    FILES
        ${SANDBOX_SOURCES}
        ${SANDBOX_HEADERS}
)

target_link_libraries(
    Sandbox
    PRIVATE
    AionEngine
)

set_target_properties(
    Sandbox
    PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY
    "$<TARGET_FILE_DIR:Sandbox>"
)

# ==================================================
# Copy Assets
# ==================================================

add_custom_command(
    TARGET Sandbox POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E make_directory
    "$<TARGET_FILE_DIR:Sandbox>/assets"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:Sandbox>/assets"
)