#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {

}

VertexBuffer::~VertexBuffer() {

}

void VertexBuffer::fillData(const int size, const void* data, GLenum usage) {
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, renderID);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}