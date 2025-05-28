#ifndef SHADER_H

#define SHADER_H

#include <GLAD/glad.h>

typedef struct {
  GLuint id;
} shader_t;

/**
 * @brief Creates a new compiled shader object.
 *
 * This function creates a new compiled shader from the `src` specified.
 *
 * @note The function copies the string, meaning the calling code is free to
 * remove the pointer.
 *
 * @param kind The kind of shader to create
 * @param src The source for the shader
 *
 * @return The compiled shader handle greather than 0, or 0 on error.
 */
shader_t shader_create(GLenum kind, const char *src);

/**
 * @brief Creates a shader from a source file.
 *
 * This functions creates a new shader with the source from the file specified
 * in `filepath`.
 *
 * @param kind The kind of shader to create
 * @param filepath The path to the source file
 *
 * @return The compiled shader handle greather than 0, or 0 on error.
 */
shader_t shader_load(GLenum kind, const char *filepath);

/**
 * @brief Checks the compile status of the shader
 *
 * This function checks the status of the compilation of the shader program. The
 * error message, if any is stored in the msg pointer passed in.
 *
 * @param shader The shader to check the status of
 * @param msg The pointer to store any error message in
 * @param size The size of the msg
 * @returns GL_TRUE to indicate successful compilation and GL_FALSE otherwise.
 */
GLint shader_get_compile_status(shader_t *shader, char *msg,
                                unsigned long size);

/**
 * @brief Destroys a shader.
 *
 * This function destroys a shader and deletes it from the current context.
 *
 * @param shader The shader to destroy
 * @returns void
 */
void shader_destroy(shader_t shader);

#endif // SHADER_H
