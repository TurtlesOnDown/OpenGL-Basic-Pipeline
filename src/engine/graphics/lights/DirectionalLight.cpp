#include "Includes.h"

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 col, glm::vec3 pos):Light(col, pos) {

}

DirectionalLight::~DirectionalLight() {

}

void DirectionalLight::use(std::shared_ptr<Shader> shader, int num) {
	std::string number = std::to_string(num);

	shader->set<glm::vec3>("dirLights[" + number + "].position", getWorldPosition());
	shader->set<glm::vec3>("dirLights[" + number + "].ambient", ambient);
	shader->set<glm::vec3>("dirLights[" + number + "].diffuse", diffuse);
	shader->set<glm::vec3>("dirLights[" + number + "].specular", specular);
}