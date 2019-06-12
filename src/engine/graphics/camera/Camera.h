#include "Includes.h"

#include "../../objects/PObject.h"

#ifndef CAMERACLASS
#define CAMERACLASS

// camera class object for use in world

class Camera : public PObject {
public:
	Camera(glm::vec3 pos = { 0.0f, 0.0f, 0.0f });
	~Camera();

	const glm::mat4 &getViewMatrix();

private:
	glm::mat4 viewMatrix;

	void updateViewMatrix();
};

#endif