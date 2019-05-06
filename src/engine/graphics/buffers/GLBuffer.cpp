#include "GLBuffer.h"

GLBuffer::GLBuffer() {
	glGenBuffers(1, &renderID);
}

GLBuffer::~GLBuffer() {
	glDeleteBuffers(1, &renderID);
}