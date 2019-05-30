#include "GLBuffer.h"

#ifndef INDEXBUFFERCLASS
#define INDEXBUFFERCLASS

// OpenGL Index Buffer abstraction

class IndexBuffer : public GLBuffer {
public:
	IndexBuffer();
	~IndexBuffer();

	virtual void fillData(const int size, const void* data, GLenum usage) override;

	virtual void bind() override;
	virtual void unbind() override;

private:
};

#endif // !INDEXBUFFER