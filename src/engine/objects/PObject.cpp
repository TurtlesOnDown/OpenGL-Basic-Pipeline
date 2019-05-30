#include "PObject.h"

#include "../import manager/material/Material.h"
#include "../import manager/model/Mesh.h"
#include "../import manager/model/Model.h"
#include "../graphics/camera/Camera.h"

glm::vec3 PObject::worldUp = { 0.0f, 1.0f, 0.0f };

PObject::PObject(glm::vec3 pos):position(pos) {
	updateVectors();
}

PObject::~PObject() {

}

void PObject::translate(glm::vec3 trans) {
	position += trans;
	updated = true;
}

void PObject::rotate(float angle, glm::vec3 axis, SPACE relativeTo) {
	glm::quat key_quat = glm::quat(axis * angle);

	switch (relativeTo)
	{
	case SPACE::WORLD:
		orientation = orientation * key_quat;
		break;
	case SPACE::LOCAL:
		orientation = key_quat * orientation;
		break;
	default:
		std::cout << "POBJECT::INVALID SPACE" << std::endl;
		break;
	}

	orientation = glm::normalize(orientation);

	updated = true;
}

const glm::vec3& PObject::getFront() {
	if (updated) {
		updateVectors();
		updated = false;
	}
	return front;
}

const glm::vec3& PObject::getRight() {
	if (updated) {
		updateVectors();
		updated = false;
	}
	return right;
}

const glm::vec3& PObject::getUp() {
	if (updated) {
		updateVectors();
		updated = false;
	}
	return up;
}

void PObject::updateVectors() {
	front = glm::vec3(0.0f, 0.0f, 1.0f) * orientation;
	right = glm::vec3(-1.0f, 0.0f, 0.0f) * orientation;
	up = glm::vec3(0.0f, 1.0f, 0.0f) * orientation;
}

void draw(PObject& m, Camera& cam, glm::mat4 &proj, const std::shared_ptr<Shader> shader) {
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> mat;
	std::shared_ptr<Model> modelMesh;

	/*if (m.components.find(COMPONENT_TYPE::MESH) != m.components.end()) {
		mesh = std::dynamic_pointer_cast<Mesh>(m.components[COMPONENT_TYPE::MESH]);
	}
	else {
		std::cout << "DRAW::UNABLE TO FIND MESH" << std::endl;
		return;
	}*/
	if (m.components.find(COMPONENT_TYPE::MATERIAL) != m.components.end()) {
		mat = std::dynamic_pointer_cast<Material>(m.components[COMPONENT_TYPE::MATERIAL]);
	}
	else {
		std::cout << "DRAW::UNABLE TO FIND MATERIAL" << std::endl;
		return;
	}
	if (m.components.find(COMPONENT_TYPE::MODEL) != m.components.end()) {
		modelMesh = std::dynamic_pointer_cast<Model>(m.components[COMPONENT_TYPE::MODEL]);
	}
	else {
		std::cout << "DRAW::UNABLE TO FIND MODEL" << std::endl;
		return;
	}

	auto meshes = modelMesh->getMeshes();
	auto materials = modelMesh->getMaterials();

	glm::mat4 model = glm::mat4_cast(m.orientation);
	model = glm::translate(model, m.position);

	shader->use();

	for (auto mats : materials) {

		mats.second.useMaterial(shader);
		shader->setMat4("model", model);
		shader->setMat4("view", cam.getViewMatrix());
		shader->setMat4("projection", proj);

		meshes[mats.first]->bindVAO();
		meshes[mats.first]->draw();
	}
	
}

