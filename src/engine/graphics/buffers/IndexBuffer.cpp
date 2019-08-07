#include "Includes.h"

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() {

}

IndexBuffer::~IndexBuffer() {

}

void IndexBuffer::fillData(const int size, const void* data, GLenum usage) {
	OpenGLAPI::bufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void IndexBuffer::bind() {
	OpenGLAPI::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
}

void IndexBuffer::unbind() {
	OpenGLAPI::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
}