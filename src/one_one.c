/*
 * Try to draw 2 triangles next to each other using glDrawArrays by adding more
 * vertices to your data. solution:
 * https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.3.hello_triangle_exercise1/hello_triangle_exercise1.cpp
 */

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "shader.h"

#define WIDTH 800
#define HEIGHT 600

void frame_buffer_resize_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main(void) {
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Exercise 1.1", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetFramebufferSizeCallback(window, frame_buffer_resize_callback);

  float verticies[] = {
      -0.8, 0.0,  0.0, // Lower Left
      -0.4, 0.8,  0.0, // Middle Top
      0.0,  0.0,  0.0, // Lower Right

      0.0,  0.0,  0.0, // Lower Left
      0.4,  -0.8, 0.0, // Middle Bottom
      0.8,  0.0,  0.0, // Lower Right
  };

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  GLint locationAttribute = 0;
  glVertexAttribPointer(locationAttribute, 3, GL_FLOAT, GL_FALSE,
                        3 * sizeof(float), 0);
  glEnableVertexAttribArray(locationAttribute);

  shader_t vShader = shader_load(GL_VERTEX_SHADER, "./shaders/vertex.glsl");
  shader_t fShader = shader_load(GL_FRAGMENT_SHADER, "./shaders/fragment.glsl");

  GLuint program;
  program = glCreateProgram();
  glAttachShader(program, vShader.id);
  glAttachShader(program, fShader.id);
  glLinkProgram(program);

  shader_destroy(vShader);
  shader_destroy(fShader);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0., 0., 0., 0.);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteProgram(program);
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glfwTerminate();

  return EXIT_SUCCESS;
}
