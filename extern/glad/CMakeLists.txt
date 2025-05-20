cmake_minimum_required(VERSION 3.15...4.0)

project(GLAD VERSION 4.6 LANGUAGES C HOMEPAGE_URL "https://glad.dav1d.de/")

add_library(glad include/GLAD/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)
