#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"

int main(void) {
  // Initialize GLFW
  glfwInit();
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Set the major version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // Set the minor version
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use Core Profile, which gives smaller version of opengl functionality
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Remove all features that are marked as depracated in the current version (Neede for Mac?)

  GLFWwindow *window = glfwCreateWindow(600, 800, "Hello Triangle", NULL, NULL);
  if (window == NULL) {
    log_error("could not create GLFW window.");
    exit(-1);
  }
}
