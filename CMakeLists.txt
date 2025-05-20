cmake_minimum_required(VERSION 3.15...4.0)

project(ogltut VERSION 0.1
               DESCRIPTION "My progress through https://learnopengl.com"
               LANGUAGES C)

add_subdirectory("extern/glfw")

add_subdirectory("src")
