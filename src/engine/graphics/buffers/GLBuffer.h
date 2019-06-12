#include "Includes.h"

#ifndef GLBUFFERCLASS
#define GLBUFFERCLASS

// Buffer Base class for others to derive from
// TODO: Edit so that buffer aren't generated on construction

class GLBuffer {
public:
	GLBuffer();
	virtual ~GLBuffer();

	virtual void fillData(const int size, const void* data, GLenum usage) = 0;

	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	unsigned int renderID;
};

#endif // !GLBUFFER
