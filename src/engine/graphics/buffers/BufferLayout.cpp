#include "BufferLayout.h"

BufferLayout::BufferLayout(): stride(0) {

}

void BufferLayout::push(unsigned int count, unsigned int type, unsigned int size, bool normalized) {
	layout.push_back({count, type, size, stride, normalized});
	stride += size * count;
}