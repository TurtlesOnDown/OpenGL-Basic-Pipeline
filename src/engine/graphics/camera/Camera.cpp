#include "Camera.h"

Camera::Camera(glm::vec3 pos):PObject(pos) {
	updateVectors();
	updateViewMatrix();
}

Camera::~Camera() {

}

const glm::mat4 &Camera::getViewMatrix() {
	if (updated) {
		updateVectors();
		updateViewMatrix();
		updated = false;
	}
	return viewMatrix;
}

void Camera::updateViewMatrix() {
	glm::mat4 rotateMat4 = glm::mat4_cast(orientation);

	glm::mat4 translateMat4 = glm::mat4(1.0f);
	translateMat4 = glm::translate(translateMat4, position);

	viewMatrix = rotateMat4 * translateMat4;
}