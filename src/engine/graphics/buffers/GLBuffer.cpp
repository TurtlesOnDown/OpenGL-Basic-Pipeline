#include "Includes.h"

#include "GLBuffer.h"

GLBuffer::GLBuffer() {
	OpenGLAPI::genBuffers(1, &renderID);
}

GLBuffer::~GLBuffer() {
	OpenGLAPI::deleteBuffers(1, &renderID);
}