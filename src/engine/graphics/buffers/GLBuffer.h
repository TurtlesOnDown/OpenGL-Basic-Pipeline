#include "../../common/Includes.h"

#ifndef GLBUFFER
#define GLBUFFER

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
