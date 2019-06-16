#include "Includes.h"

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 col, glm::vec3 pos):Light(col, pos) {

}

DirectionalLight::~DirectionalLight() {

}

void DirectionalLight::use(std::shared_ptr<Shader> shader, int num) {
	std::string number = std::to_string(num);

	shader->setVec3("dirLights[" + number + "].direction", glm::vec3{0.0f, 0.0f, 0.0f} - position);
	shader->setVec3("dirLights[" + number + "].ambient", ambient);
	shader->setVec3("dirLights[" + number + "].diffuse", diffuse);
	shader->setVec3("dirLights[" + number + "].specular", specular);
}