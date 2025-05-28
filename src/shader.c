#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shader.h"

shader_t shader_create(GLenum kind, const char *src) {
  shader_t shader = {.id = 0};

  shader.id = glCreateShader(kind);

  if (!shader.id) {
    return shader;
  }

  glShaderSource(shader.id, 1, &src, NULL);
  glCompileShader(shader.id);

  return shader;
}

shader_t shader_load(GLenum kind, const char *filepath) {
  shader_t shader = {.id = 0};

  FILE *file = fopen(filepath, "rb");
  if (!file) {
    return shader;
  }

  if (fseek(file, 0, SEEK_END) == -1) {
    return shader;
  }

  long size = ftell(file);
  if (size == -1) {
    return shader;
  }

  rewind(file);

  char *src = calloc(1, size + 1);

  fread(src, size, 1, file);

  shader = shader_create(kind, src);
  free(src);

  return shader;
}

GLint shader_get_compile_status(shader_t *shader, char *msg,
                                unsigned long size) {
  if (shader == NULL || shader->id == 0) {
    strncpy(msg, "shader unintialized", size);
    return GL_FALSE;
  }

  int shader_ok;
  glGetShaderiv(shader->id, GL_COMPILE_STATUS, &shader_ok);

  if (shader_ok != GL_TRUE) {
    glGetShaderInfoLog(shader->id, size, NULL, msg);
    return GL_FALSE;
  }

  return GL_TRUE;
}

void shader_destroy(shader_t shader) { glDeleteShader(shader.id); }
