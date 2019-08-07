#include "Includes.h"

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {

}

VertexBuffer::~VertexBuffer() {

}

void VertexBuffer::fillData(const int size, const void* data, GLenum usage) {
	OpenGLAPI::bufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::bind() {
	OpenGLAPI::bindBuffer(GL_ARRAY_BUFFER, renderID);
}

void VertexBuffer::unbind() {
	OpenGLAPI::bindBuffer(GL_ARRAY_BUFFER, 0);
}