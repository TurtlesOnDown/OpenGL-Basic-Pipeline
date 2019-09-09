#pragma once

#include "Includes.h"

#include "../../objects/PObject.h"

// camera class object for use in world

enum class PERSPECTIVE_CONFIG { PROJECTION, ORTHOGRAPHIC };

class Camera : public PObject {
public:
	Camera(glm::mat4 perspMatrix, PERSPECTIVE_CONFIG c, glm::vec3 pos = { 0.0f, 0.0f, 0.0f });
	~Camera();

	void setPerspectiveMatrix(float FOV, float aspectRatio, float nearPlane, float farPlane);
	void setOrthographicMatrix(float left, float right, float bottom, float top, float zNear, float zFar);

	const glm::mat4 &getViewMatrix();
	const glm::mat4 &getPerspectiveMatrix() { return perspectiveMatrix; }
	const PERSPECTIVE_CONFIG getConfig() { return config; }

private:
	glm::mat4 viewMatrix;
	glm::mat4 perspectiveMatrix;
	PERSPECTIVE_CONFIG config;

	void updateViewMatrix();
};