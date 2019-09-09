#include "Includes.h"

#include "Camera.h"

Camera::Camera(glm::mat4 perspMatrix, PERSPECTIVE_CONFIG c, glm::vec3 pos):
			PObject(pos), config(c), 
			perspectiveMatrix(perspMatrix) {
	updateViewMatrix();
}

Camera::~Camera() {

}

void Camera::setPerspectiveMatrix(float FOV, float aspectRatio, float nearPlane, float farPlane) {
	config = PERSPECTIVE_CONFIG::PROJECTION;
	perspectiveMatrix = glm::perspective(FOV, aspectRatio, nearPlane, farPlane);
}

void Camera::setOrthographicMatrix(float left, float right, float bottom, float top, float zNear, float zFar) {
	config = PERSPECTIVE_CONFIG::ORTHOGRAPHIC;
	perspectiveMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
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