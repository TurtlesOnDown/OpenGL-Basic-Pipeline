#include "Includes.h"

#include "PObject.h"

#include "../import manager/material/Material.h"
#include "../import manager/model/Mesh.h"
#include "../import manager/model/Model.h"
#include "../graphics/camera/Camera.h"

PObject::PObject(glm::vec3 pos, glm::vec3 s):localPosition(pos), localScale(s) {

}

PObject::~PObject() {

}

void PObject::onUpdate() {

}
void PObject::onEvent(Event &e) {

}

void PObject::onUpdateChildren() {
	onUpdate();
	for (auto child : children) {
		child->onUpdateChildren();
	}
}

void PObject::translate(glm::vec3 trans) {
	localPosition += trans;
}

void PObject::scaleAdd(glm::vec3 s) {
	localScale += s;
}

void PObject::scaleMult(glm::vec3 s) {
	localScale *= s;
}

void PObject::rotate(float angle, glm::vec3 axis, SPACE relativeTo) {
	glm::quat key_quat = glm::quat(axis * angle);

	switch (relativeTo)
	{
	case SPACE::WORLD:
		localOrientation = localOrientation * key_quat;
		break;
	case SPACE::LOCAL:
		localOrientation = key_quat * localOrientation;
		break;
	default:
		LOG_WARN("POBJECT::INVALID SPACE");
		break;
	}

	localOrientation = glm::normalize(localOrientation);
}

glm::mat4 PObject::getModelMatrix() {
	glm::mat4 parentModel = glm::mat4(1.0f);
	if (getParent() != nullptr) {
		parentModel = getParent()->getModelMatrix();
	}

	glm::mat4 localModel = glm::translate(glm::mat4(1.0f), localPosition);
	localModel *= glm::mat4_cast(localOrientation);
	localModel *= glm::scale(glm::mat4(1.0f), localScale);
	return parentModel * localModel;
}

glm::vec3 PObject::getWorldFront() const {
	return glm::vec3(0.0f, 0.0f, -1.0f) * getWorldOrienation();
}

glm::vec3 PObject::getWorldRight() const {
	return glm::vec3(1.0f, 0.0f, 0.0f) * getWorldOrienation();
}

glm::vec3 PObject::getWorldUp() const {
	return glm::vec3(0.0f, 1.0f, 0.0f) * getWorldOrienation();
}

glm::vec3 PObject::getWorldPosition() const {
	auto worldPos = localPosition;

	if (getParent() != nullptr) {
		worldPos = glm::vec3(getParent()->getModelMatrix() * glm::vec4(localPosition, 1.0f));
	}

	return worldPos;
}

glm::quat PObject::getWorldOrienation() const {
	auto parentPtr = getParent();
	auto worldOrient = localOrientation;
	while (parentPtr != nullptr) {
		worldOrient = parentPtr->localOrientation * worldOrient;
		parentPtr = parentPtr->getParent();
	}
	return worldOrient;
}

void PObject::addChild(std::shared_ptr<PObject> parent, std::shared_ptr<PObject> child) {
	parent->children.push_back(child);
	child->parent = parent;
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

	for (auto mats : materials) {

		mats.second.useMaterial(shader);
		shader->set<glm::mat4>("model", getModelMatrix());

		meshes[mats.first]->bindVAO();
		meshes[mats.first]->draw();
	}
	
}

