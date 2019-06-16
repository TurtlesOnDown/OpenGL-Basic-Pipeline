#include "Includes.h"

#ifndef BUFFERLAYOUTCLASS
#define BUFFERLAYOUTCLASS

struct BufferElement {
	unsigned int count;
	unsigned int type;
	unsigned int size;
	unsigned int offset;
	bool normalized;
};

// Layout class for VertexArrayObjects
// TODO: Add functions for other data types

class BufferLayout {
public:
	BufferLayout();

	template<typename T>
	void Push(unsigned int count = 1, bool normalized = false)
	{
		LOG_WARN("BUFFERLAYOUT::INCORRECT TYPE");
	}

	template<>
	void Push<float>(unsigned int count, bool normalized)
	{
		push(count, GL_FLOAT, sizeof(float), normalized);
	}

	inline const std::vector<BufferElement> &getLayout() const { return layout; };
	inline unsigned int getStride() const { return stride; };
	
private:
	unsigned int stride;
	std::vector<BufferElement> layout;

	void push(unsigned int count, unsigned int type, unsigned int size, bool normalized);
};

#endif // !BUFFERLAYOUT


