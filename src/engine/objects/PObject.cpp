#include "PObject.h"

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

