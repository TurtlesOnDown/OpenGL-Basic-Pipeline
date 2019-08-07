#pragma once

class OpenGLAPI {
public:

	static void LogError(const char* function, const char* file, int line);

	static void genBuffers(GLsizei n, GLuint *buffers);
	static void deleteBuffers(GLsizei n, GLuint *buffers);
	static void bindBuffer(GLenum target, GLuint buffer);
	static void bufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);

	static void genVertexArray(GLsizei n, GLuint *arrays);
	static void deleteVertexArrays(GLsizei n, const GLuint *arrays);
	static void bindVertexArray(GLuint array);
	static void enableVertexAttribArray(GLuint index);
	static void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);

	static void genTextures(GLsizei n, GLuint *textures);
	static void bindTexture(GLenum target, GLuint texture);
	static void texParameteri(GLenum target, GLenum pname, GLint param);
	static void activeTexture(GLenum texture);
	static void generateMipmap(GLenum target);
	static void texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *data);

	static void enable(GLenum cap);
	static void clear(GLbitfield mask);
	static void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	static void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);

	static void viewport(GLint x, GLint y, GLsizei width, GLsizei height);

private:
};