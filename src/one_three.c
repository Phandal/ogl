/*
 * Create two shader programs where the second program uses a different fragment
 * shader that outputs the color yellow; draw both triangles again where one
 * outputs the color yellow. solution:
 * https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.5.hello_triangle_exercise3/hello_triangle_exercise3.cpp
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

void setup_triangle(GLuint vao, GLuint vbo, float *verticies, size_t n) {
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, n, verticies, GL_STATIC_DRAW);
  GLint locationAttribute = 0;
  glVertexAttribPointer(locationAttribute, 3, GL_FLOAT, GL_FALSE,
                        3 * sizeof(float), 0);
  glEnableVertexAttribArray(locationAttribute);
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

  float triangle_one[] = {
      -0.8, 0.0, 0.0, // Lower Left
      -0.4, 0.8, 0.0, // Middle Top
      0.0,  0.0, 0.0, // Lower Right
  };

  float triangle_two[] = {
      0.0, 0.0,  0.0, // Lower Left
      0.4, -0.8, 0.0, // Middle Bottom
      0.8, 0.0,  0.0, // Lower Right
  };

  GLuint vaos[2] = {0};
  glGenVertexArrays(2, vaos);

  GLuint vbos[2] = {0};
  glGenBuffers(2, vbos);

  // Triangle One
  setup_triangle(vaos[0], vbos[0], triangle_one, sizeof(triangle_one));
  setup_triangle(vaos[1], vbos[1], triangle_two, sizeof(triangle_two));

  shader_t vShader = shader_load(GL_VERTEX_SHADER, "./shaders/vertex.glsl");
  shader_t redFShader =
      shader_load(GL_FRAGMENT_SHADER, "./shaders/fragment_red.glsl");
  shader_t yellowFShader =
      shader_load(GL_FRAGMENT_SHADER, "./shaders/fragment_yellow.glsl");

  GLuint redProgram;
  redProgram = glCreateProgram();
  glAttachShader(redProgram, vShader.id);
  glAttachShader(redProgram, redFShader.id);
  glLinkProgram(redProgram);

  GLuint yellowProgram = glCreateProgram();
  glAttachShader(yellowProgram, vShader.id);
  glAttachShader(yellowProgram, yellowFShader.id);
  glLinkProgram(yellowProgram);

  shader_destroy(vShader);
  shader_destroy(redFShader);
  shader_destroy(yellowFShader);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0., 0., 0., 0.);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(redProgram);
    glBindVertexArray(vaos[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(yellowProgram);
    glBindVertexArray(vaos[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteProgram(redProgram);
  glDeleteProgram(yellowProgram);
  glDeleteVertexArrays(2, vaos);
  glDeleteBuffers(2, vbos);
  glfwTerminate();

  return EXIT_SUCCESS;
}
