add_executable(window window.c log.c log.h shader.c shader.h)

set_target_properties(window PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

if (WIRE_FRAME)
  target_compile_definitions(window PUBLIC WIRE_FRAME)
endif()

file(GLOB SHADERS "${CMAKE_SOURCE_DIR}/src/shaders/*")
foreach (SHADER ${SHADERS})
  get_filename_component(SHADER_NAME ${SHADER} NAME)
  configure_file("${SHADER}" "${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME}" COPYONLY)
endforeach()

target_link_libraries(window glad)
target_link_libraries(window glfw)
