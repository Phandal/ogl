cmake_minimum_required(VERSION 3.15...4.0)

project(ogltut VERSION 0.1
               DESCRIPTION "My progress through https://learnopengl.com"
               LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")

add_subdirectory("extern/glfw")
add_subdirectory("extern/glad")

option(WIRE_FRAME PUBLIC OFF)
add_subdirectory("src")
