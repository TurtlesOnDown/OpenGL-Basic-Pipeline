#include "Includes.h"

#include "Camera.h"

Camera::Camera(glm::vec3 pos):PObject(pos) {
	updateViewMatrix();
}

Camera::~Camera() {

}

const glm::mat4 &Camera::getViewMatrix() {
	updateViewMatrix();

	return viewMatrix;
}

void Camera::updateViewMatrix() {
	glm::mat4 rotateMat4 = glm::mat4_cast(localOrientation);

	glm::mat4 translateMat4 = glm::mat4(1.0f);
	translateMat4 = glm::translate(translateMat4, -getWorldPosition());

	viewMatrix = rotateMat4 * translateMat4;
}