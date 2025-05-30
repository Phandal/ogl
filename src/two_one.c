#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "shader.h"

#define WIDTH 800
#define HEIGHT 600

void frame_buffer_resize(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main(void) {
  if (!glfwInit()) {
    log_error("failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Exercises 2", NULL, NULL);
  if (window == NULL) {
    log_error("failed to create window");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    log_error("failed to initialize GLAD");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetFramebufferSizeCallback(window, frame_buffer_resize);

  float verticies[] = {
      -0.5, 0.5,  0.0, 1.0, 0.0, 0.0, // Top Left
      0.5,  0.5,  0.0, 0.0, 1.0, 0.0, // Top Right
      0.0,  -0.5, 0.0, 0.0, 0.0, 1.0, // Middle Bottom
  };

  GLuint vertexArray;
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  shader_t vertexShader = shader_load(GL_VERTEX_SHADER, "shaders/vertex.glsl");
  shader_t fragmentShader =
      shader_load(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");

  GLuint program;
  program = glCreateProgram();
  glAttachShader(program, vertexShader.id);
  glAttachShader(program, fragmentShader.id);
  glLinkProgram(program);
  glUseProgram(program); // NOTE: must set it here in order to get the attribute
                         // location at runtime

  GLuint positionAttribute = glGetAttribLocation(program, "aPos");
  GLuint colorAttribute = glGetAttribLocation(program, "aColor");

  glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                        sizeof(float) * 6, (void *)0);
  glEnableVertexAttribArray(positionAttribute);

  glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE,
                        sizeof(float) * 6, (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(colorAttribute);

  shader_destroy(vertexShader);
  shader_destroy(fragmentShader);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteVertexArrays(1, &vertexArray);
  glDeleteProgram(program);

  glfwTerminate();

  return EXIT_SUCCESS;
}
