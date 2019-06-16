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

	shader->setVec3("spotLights[" + number + "].position", position);
	shader->setVec3("spotLights[" + number + "].direction", getFront());

	shader->setFloat("spotLights[" + number + "].constant", constantAttenuation);
	shader->setFloat("spotLights[" + number + "].linear", linearAttenuation);
	shader->setFloat("spotLights[" + number + "].quadratic", quadraticAttenuation);

	shader->setFloat("spotLights[" + number + "].cutOff", cutOff);
	shader->setFloat("spotLights[" + number + "].outerCutOff", outerCutOff);

	shader->setVec3("spotLights[" + number + "].ambient", ambient);
	shader->setVec3("spotLights[" + number + "].diffuse", diffuse);
	shader->setVec3("spotLights[" + number + "].specular", specular);

	
}