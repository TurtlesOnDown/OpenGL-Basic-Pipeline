#include "Includes.h"

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
		LOG_WARN("POBJECT::INVALID SPACE");
		break;
	}

	orientation = glm::normalize(orientation);

	updateVectors();
}

const glm::vec3& PObject::getFront() {
	return front;
}

const glm::vec3& PObject::getRight() {
	return right;
}

const glm::vec3& PObject::getUp() {
	return up;
}

void PObject::updateVectors() {
	front = glm::vec3(0.0f, 0.0f, -1.0f) * orientation;
	right = glm::vec3(1.0f, 0.0f, 0.0f) * orientation;
	up = glm::vec3(0.0f, 1.0f, 0.0f) * orientation;
}

void PObject::draw(const std::shared_ptr<Shader> shader) {
	std::shared_ptr<Model> modelMesh;

	if (components.find(COMPONENT_TYPE::MODEL) != components.end()) {
		modelMesh = std::dynamic_pointer_cast<Model>(components[COMPONENT_TYPE::MODEL]);
	}
	else {
		LOG_INFO("DRAW::UNABLE TO FIND MODEL");
		return;
	}

	auto meshes = modelMesh->getMeshes();
	auto materials = modelMesh->getMaterials();

	glm::mat4 model = glm::mat4_cast(orientation);
	model = glm::translate(model, position);

	for (auto mats : materials) {

		mats.second.useMaterial(shader);
		shader->setMat4("model", model);

		meshes[mats.first]->bindVAO();
		meshes[mats.first]->draw();
	}
	
}

