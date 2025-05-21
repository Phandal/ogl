#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"

#define WIDTH 800
#define HEIGHT 600

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main(void) {
  if (glfwInit() != GL_TRUE) {
    log_error("could not initialize GLFW");
    exit(-1);
  }
  log_info("GLFW initialized");
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Set the major version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // Set the minor version
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use Core Profile, which gives smaller version of opengl functionality
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Remove all features that are marked as depracated in the current version (Neede for Mac?)

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Window", NULL, NULL);
  if (window == NULL) {
    log_error("could not create GLFW window");
    glfwTerminate();
    exit(-1);
  }
  log_info("created GLFW window");
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    log_error("could not initialize GLAD");
    glfwTerminate();
    exit(-1);
  }
  log_info("GLAD initialized");

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  log_info("set frame buffer size callback");

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  log_info("shutting down");
  glfwDestroyWindow(window);
  log_info("destroyed window");

  glfwTerminate();
  log_info("GLFW deinitialized");

  return 0;
}
