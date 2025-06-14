#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <bmp.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "shader.h"

#define WIDTH 800
#define HEIGHT 600
#define MESSAGE_SIZE 512

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void error_callback(int code, const char *msg) {
  log_error("GLFW: %d | %s", code, msg);
  return;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main(void) {

  vec4 output;
  vec4 vec = {1.0, 0.0, 0.0, 1.0};
  vec3 translate = {1.0, 1.0, 0.0};
  mat4 mat;

  glm_translate_make(mat, translate);
  glm_mat4_mulv(mat, vec, output);
  printf("%f, %f, %f\n", output[0], output[1], output[2]);
  exit(0);

  if (glfwInit() != GL_TRUE) {
    log_error("could not initialize GLFW");
    exit(EXIT_FAILURE);
  }
  log_info("GLFW initialized");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Set the major version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // Set the minor version
  glfwWindowHint(
      GLFW_OPENGL_PROFILE,
      GLFW_OPENGL_CORE_PROFILE); // Use Core Profile, which gives smaller
                                 // version of opengl functionality
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE); // Remove all features that are marked as depracated
                           // in the current version (Neede for Mac?)
#endif

  glfwSetErrorCallback(error_callback);
  log_info("set error callback");

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Hello Window", NULL, NULL);
  if (window == NULL) {
    log_error("could not create GLFW window");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  log_info("created GLFW window");
  glfwMakeContextCurrent(window);
  log_info("made glfw context current");

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    log_error("could not initialize GLAD");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  log_info("GLAD initialized");

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  log_info("set frame buffer size callback");

  /*
    A Vertex is a collection of data around a 3D point. Vertex data is stored in
    Vertex Attributes that can contain any data.
   */
  // Setting up the Vertices to draw a triangle
  float vertices[] = {
      /*     Positions           Colors      Texture Coords     */
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Top Left
  };

  unsigned int indices[] = {
      0, 1, 3, // First Triangle
      3, 1, 2, // Second Triangle
  };

  /*
    A Vertex Array Object stores any vertex attributes that are made while this
    VAO is bound and which Vertex Buffers are used for those attributes. The VAO
    can then be bound later to restore the state of the vertex attributes.
   */
  // Creating a Vertex Array Object
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  log_info("bound vertex array object");

  /*
    A Vertex Buffer Object is a way to store data on the GPU instead of having
    to send data to the GPU point by point.
   */
  // Setting up the vertex buffer object
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  log_info("bound vertex buffer object");

  // Setting up element buffer object
  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  log_info("bound element buffer object");

  // Explain how to interpret the vertex data in the vertex buffer object
  GLint positionAttribute = 0;
  GLint colorAttribute = 1;
  GLint textureCoordinateAttribute = 2;

  glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(positionAttribute);
  log_info("enabled position vertex attribute");

  glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(colorAttribute);
  log_info("enabled color vertex attribute");

  glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, GL_FALSE,
                        8 * sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(textureCoordinateAttribute);
  log_info("enabled texture coordinate vertex attribute");

  // Loading images
  bmp_image_t *containerImage = bmp_load("images/container.bmp");
  if (!containerImage) {
    log_error("could not load container image");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  log_info("loaded container image");

  bmp_image_t *smileyImage = bmp_load("images/smiley.bmp");
  if (!smileyImage) {
    log_error("could not load smiley image");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  log_info("loaded smiley image");

  // Setting up a texture
  GLuint textures[2];
  glGenTextures(2, textures);
  log_info("generated textures");

  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, containerImage->info.width,
               containerImage->info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               (uint8_t *)containerImage->pixel);
  glGenerateMipmap(GL_TEXTURE_2D);
  log_info("generated container texture mipmap");

  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, smileyImage->info.width,
               smileyImage->info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               (uint8_t *)smileyImage->pixel);
  glGenerateMipmap(GL_TEXTURE_2D);
  log_info("generated smiley texture mipmap");

  bmp_destroy(containerImage);
  bmp_destroy(smileyImage);
  log_info("unloaded images");

  /*
    A Shader is a program that runs on the GPU. It can come in many different
    formats.
   */
  // Compiling shaders
  char msg[MESSAGE_SIZE] = "unknown";
  shader_t vertexShader;
  vertexShader = shader_load(GL_VERTEX_SHADER, "shaders/vertex.glsl");
  if (vertexShader.id == 0 ||
      !shader_get_compile_status(&vertexShader, msg, MESSAGE_SIZE)) {
    log_error("could not create vertex shader %s\n", msg);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  log_info("compiled vertex shader");

  shader_t fragmentShader;
  fragmentShader = shader_load(GL_FRAGMENT_SHADER, "shaders/fragment.glsl");
  if (fragmentShader.id == 0 ||
      !shader_get_compile_status(&fragmentShader, msg, MESSAGE_SIZE)) {
    log_error("could not create fragment shader %s\n", msg);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  log_info("compiled fragment shader");

  // Creating program NOTE: attaching shaders links the outputs of the previous
  // shader to the inputs of the next shdader
  GLuint program;
  program = glCreateProgram();
  log_info("created program");
  glAttachShader(program, vertexShader.id);
  log_info("attached vertex shader");
  glAttachShader(program, fragmentShader.id);
  log_info("attached fragment shader");
  glLinkProgram(program);

  // Checking for errors when linking
  GLint result;
  glGetProgramiv(program, GL_LINK_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(program, MESSAGE_SIZE, NULL, msg);
    log_error("Failed to link: %s", msg);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  log_info("program linked");

  // Use the program created
  glUseProgram(program);
  log_info("using program");

  // Setting texture sampler locations
  GLuint containerSamplerLocation =
      glGetUniformLocation(program, "containerTexture");
  GLuint smileySamplerLocation = glGetUniformLocation(program, "smileyTexture");
  glUniform1i(containerSamplerLocation, 0);
  glUniform1i(smileySamplerLocation, 1);
  log_info("set sampler locations manually");

  // Cleanup of the shaders after they were used in the program
  shader_destroy(vertexShader);
  shader_destroy(fragmentShader);
  log_info("shaders deleted");

#ifdef WIRE_FRAME
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  log_info("set draw mode to wireframe");
#endif

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  log_info("vertex array object deleted");

  glDeleteBuffers(1, &VBO);
  log_info("vertex buffer object deleted");

  glDeleteBuffers(1, &EBO);
  log_info("element buffer object deleted");

  glDeleteBuffers(2, textures);
  log_info("texture buffer object deleted");

  glDeleteProgram(program);
  log_info("program deleted");

  log_info("shutting down");
  glfwDestroyWindow(window);
  log_info("destroyed window");

  glfwTerminate();
  log_info("GLFW deinitialized");

  log_info("shut down successfully");

  return 0;
}
