#include "Includes.h"

#include "BufferLayout.h"

#ifndef VERTEXARRAYOBJECTCLASS
#define VERTEXARRAYOBJECTCLASS

// OpenGL VertexArrayObject abstraction

class VertexArrayObject {
public:
	VertexArrayObject();
	~VertexArrayObject();

	void formatBuffer(const BufferLayout &layout);

	void bind();
	void unbind();
private:
	unsigned int renderID;
};

#endif // !VERTEXARRAYOBJECT
