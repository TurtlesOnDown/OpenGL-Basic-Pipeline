#include "Includes.h"

#include "Mesh.h"

BufferLayout Mesh::bufflayout;

Mesh::Mesh(const std::vector<Vertex>& verts, const std::vector<unsigned int>& ind):Component((COMPONENT_TYPE)0) {
	setVertices(verts);
	setIndices(ind);

	if (bufflayout.getLayout().size() == 0) {
		bufflayout.Push<float>(3, false);
		bufflayout.Push<float>(3, false);
		bufflayout.Push<float>(2, false);
		bufflayout.Push<float>(3, false);
		bufflayout.Push<float>(3, false);
	}
}

Mesh::~Mesh() {

}

void Mesh::fillAndFormatVAO() {
	vertArrayObj.bind();

	vertBuffer.bind();
	indexBuffer.bind();
	fillData(&vertBuffer, &indexBuffer, GL_STATIC_DRAW);

	formatBuffer(&vertArrayObj);
}

void Mesh::fillData(GLBuffer* vertBuffer, GLBuffer* indBuffer, GLenum usage) {
	if (vertBuffer != nullptr) {
		vertBuffer->fillData(vertices.size() * sizeof(Vertex), &vertices[0], usage);
	}
	if (indBuffer != nullptr) {
		indBuffer->fillData(indices.size() * sizeof(unsigned int), &indices[0], usage);
	}

}

void Mesh::formatBuffer(VertexArrayObject* vertBuffer) {
	vertBuffer->formatBuffer(bufflayout);
}

void Mesh::bindVAO() {
	vertArrayObj.bind();
}

void Mesh::draw() {
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::setVertices(const std::vector<Vertex>& verts) {
	vertices = verts;
}

void Mesh::setIndices(const std::vector<unsigned int>& ind) {
	indices = ind;
}