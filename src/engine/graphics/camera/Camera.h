#include "../../objects/PObject.h"


#ifndef CAMERA
#define CAMERA

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