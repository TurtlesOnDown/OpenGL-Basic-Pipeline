#include "Includes.h"

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() {

}

IndexBuffer::~IndexBuffer() {

}

void IndexBuffer::fillData(const int size, const void* data, GLenum usage) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
}