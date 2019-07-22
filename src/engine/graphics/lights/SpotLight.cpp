#include "Includes.h"

#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 color, glm::vec3 pos):PointLight(color, pos) {
	cutOff = glm::cos(glm::radians(12.5f));
	outerCutOff = glm::cos(glm::radians(17.5f));
}

SpotLight::~SpotLight() {

}

void SpotLight::use(std::shared_ptr<Shader> shader, int num) {
	std::string number = std::to_string(num);

	shader->set<glm::vec3>("spotLights[" + number + "].position", getWorldPosition());
	shader->set<glm::vec3>("spotLights[" + number + "].direction", getWorldFront());

	shader->set<float>("spotLights[" + number + "].constant", constantAttenuation);
	shader->set<float>("spotLights[" + number + "].linear", linearAttenuation);
	shader->set<float>("spotLights[" + number + "].quadratic", quadraticAttenuation);

	shader->set<float>("spotLights[" + number + "].cutOff", cutOff);
	shader->set<float>("spotLights[" + number + "].outerCutOff", outerCutOff);

	shader->set<glm::vec3>("spotLights[" + number + "].ambient", ambient);
	shader->set<glm::vec3>("spotLights[" + number + "].diffuse", diffuse);
	shader->set<glm::vec3>("spotLights[" + number + "].specular", specular);

	
}