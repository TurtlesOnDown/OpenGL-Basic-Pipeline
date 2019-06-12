#include "Includes.h"

#include "../../objects/Component.h"
#include "../../graphics/buffers/BufferLayout.h"
#include "../../graphics/buffers/VertexBuffer.h"
#include "../../graphics/buffers/IndexBuffer.h"
#include "../../graphics/buffers/VertexArrayObject.h"

#ifndef MESHCLASS
#define MESHCLASS

// Class to house Vertex and Index informations for 3D Objects

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

class Mesh : public Component {
public:
	Mesh(const std::vector<Vertex> &verts, const std::vector<unsigned int> &ind);
	~Mesh();

	void fillAndFormatVAO();

	void setVertices(const std::vector<Vertex>& verts);
	void setIndices(const std::vector<unsigned int>& ind);

	void fillData(GLBuffer *vertBuffer, GLBuffer *indBuffer, GLenum usage);
	void formatBuffer(VertexArrayObject* vertBuffer);
	void bindVAO();
	void draw();

	const std::vector<Vertex>& getVertices() const { return vertices; }
	const std::vector<unsigned int>& getIndices() const { return indices; }

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	VertexBuffer vertBuffer;
	VertexArrayObject vertArrayObj;
	IndexBuffer indexBuffer;

	static BufferLayout bufflayout;
};

#endif