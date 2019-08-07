#include "Includes.h"

#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
	OpenGLAPI::genVertexArray(1, &renderID);
}

VertexArrayObject::~VertexArrayObject() {
	OpenGLAPI::deleteVertexArrays(1, &renderID);
}

void VertexArrayObject::formatBuffer(const BufferLayout& layout) {
	const auto elements = layout.getLayout();
	for (unsigned int i = 0; i < elements.size(); ++i) {
		const auto element = elements[i];
		OpenGLAPI::vertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (void*)element.offset);
		OpenGLAPI::enableVertexAttribArray(i);
	}
}

void VertexArrayObject::bind() {
	OpenGLAPI::bindVertexArray(renderID);
}

void VertexArrayObject::unbind() {
	OpenGLAPI::bindVertexArray(0);
}