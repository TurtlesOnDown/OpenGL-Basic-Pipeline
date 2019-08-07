#include "Includes.h"

#include "OpenGLAPI.h"

#ifdef DEBUG
#define GLCHECK_ERROR(x) OpenGLAPI::LogError(#x, __FILE__, __LINE__);\
	x;\
	OpenGLAPI::LogError(#x, __FILE__, __LINE__)

#else
#define GLCHECK_ERROR(x) x

#endif // DEBUG

void OpenGLAPI::LogError(const char *function, const char *file, int line) {
	while (GLenum error = glGetError()) {
		LOG_ERROR("OpenGL Error::{0}, {1}, {2}, {3}", error, function, file, line);
	}
}

void  OpenGLAPI::genBuffers(GLsizei num, GLuint *ref) {
	GLCHECK_ERROR(glGenBuffers(num, ref));
}

void OpenGLAPI::deleteBuffers(GLsizei num, GLuint *ref) {
	GLCHECK_ERROR(glDeleteBuffers(num, ref));
}

void OpenGLAPI::bindBuffer(GLenum target, GLuint buffer) {
	GLCHECK_ERROR(glBindBuffer(target, buffer));
}

void OpenGLAPI::bufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) {
	GLCHECK_ERROR(glBufferData(target, size, data, usage));
}

void OpenGLAPI::genVertexArray(GLsizei n, GLuint *arrays) {
	GLCHECK_ERROR(glGenVertexArrays(n, arrays));
}

void OpenGLAPI::deleteVertexArrays(GLsizei n, const GLuint *arrays) {
	GLCHECK_ERROR(glDeleteVertexArrays(n, arrays));
}

void OpenGLAPI::bindVertexArray(GLuint array) {
	GLCHECK_ERROR(glBindVertexArray(array));
}

void OpenGLAPI::enableVertexAttribArray(GLuint index) {
	GLCHECK_ERROR(glEnableVertexAttribArray(index));
}

void OpenGLAPI::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) {
	GLCHECK_ERROR(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
}

void OpenGLAPI::genTextures(GLsizei n, GLuint *textures) {
	GLCHECK_ERROR(glGenTextures(n, textures));
}

void OpenGLAPI::bindTexture(GLenum target, GLuint texture) {
	GLCHECK_ERROR(glBindTexture(target, texture));
}

void OpenGLAPI::texParameteri(GLenum target, GLenum pname, GLint param) {
	GLCHECK_ERROR(glTexParameteri(target, pname, param));
}

void OpenGLAPI::activeTexture(GLenum texture) {
	GLCHECK_ERROR(glActiveTexture(texture));
}

void OpenGLAPI::generateMipmap(GLenum target) {
	GLCHECK_ERROR(glGenerateMipmap(target));
}

void OpenGLAPI::texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *data) {
	GLCHECK_ERROR(glTexImage2D(target, level, internalformat, width, height, border, format, type, data));
}

void OpenGLAPI::enable(GLenum cap) {
	GLCHECK_ERROR(glEnable(cap));
}

void OpenGLAPI::clear(GLbitfield mask) {
	GLCHECK_ERROR(glClear(mask));
}

void OpenGLAPI::clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	GLCHECK_ERROR(glClearColor(red, green, blue, alpha));
}

void OpenGLAPI::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) {
	GLCHECK_ERROR(glDrawElements(mode, count, type, indices));
}

void OpenGLAPI::viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
	GLCHECK_ERROR(glViewport(x, y, width, height));
}