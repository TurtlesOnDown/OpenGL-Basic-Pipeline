#include "Includes.h"

#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
	glGenVertexArrays(1, &renderID);
}

VertexArrayObject::~VertexArrayObject() {
	glDeleteVertexArrays(1, &renderID);
}

void VertexArrayObject::formatBuffer(const BufferLayout& layout) {
	const auto elements = layout.getLayout();
	for (unsigned int i = 0; i < elements.size(); ++i) {
		const auto element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (void*)element.offset);
		glEnableVertexAttribArray(i);
	}
}

void VertexArrayObject::bind() {
	glBindVertexArray(renderID);
}

void VertexArrayObject::unbind() {
	glBindVertexArray(0);
}