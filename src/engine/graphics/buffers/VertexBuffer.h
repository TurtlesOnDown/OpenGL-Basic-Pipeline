#include "GLBuffer.h"

#ifndef VERTEXBUFFER
#define VERTEXBUFFER

class VertexBuffer : public GLBuffer {
public:
	VertexBuffer();
	~VertexBuffer();

	virtual void fillData(const int size, const void* data, GLenum usage) override;

	virtual void bind() override;
	virtual void unbind() override;

private:
};

#endif // !VERTEXBUFFER
