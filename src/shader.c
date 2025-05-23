#include <stdio.h>
#include <stdlib.h>

#include "shader.h"

#define MESSAGE_SIZE 512

shader_t *shader_create(GLenum kind, const char *src) {
  char msg[MESSAGE_SIZE] = {0};
  shader_t *shader = malloc(sizeof(shader_t));
  if (!shader) {
    return NULL;
  }

  shader->kind = kind;
  shader->id = glCreateShader(kind);

  if (!shader->id) {
    shader_destroy(shader);
    return NULL;
  }

  glShaderSource(shader->id, 1, &src, NULL);
  glCompileShader(shader->id);

  return shader;
}

shader_t *shader_load(GLenum kind, const char *filepath) {
  FILE *f = fopen(filepath, "r");
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  rewind(f);

  char *src = malloc(size + 1);
  fread(src, size, 1, f);

  shader_t *shader = shader_create(kind, src);
  free(src);

  return shader;
}

void shader_destroy(shader_t *shader) {
  if (!shader) {
    return;
  }

  glDeleteShader(shader->id);
  free(shader);
}

/* Old Way
GLuint compileShader(GLint type, const char *tag, const char **source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, source, NULL);
  glCompileShader(shader);

  // Check for errors in the vertex shader compilation
  GLint result;
  char msg[MESSAGE_SIZE];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if (!result) {
    glGetShaderInfoLog(shader, MESSAGE_SIZE, NULL, msg);
    log_error("Failed to compile '%s': %s", tag, msg);
  }
  return shader;
}
*/
