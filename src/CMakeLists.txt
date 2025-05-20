find_package(OpenGL REQUIRED)

add_executable(window window.c)
set_target_properties(window PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
target_link_libraries(window glfw)
target_link_libraries(window OpenGL::GL)
