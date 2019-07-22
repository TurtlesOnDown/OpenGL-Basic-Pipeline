#include "Includes.h"

#include "PointLight.h"

PointLight::PointLight(glm::vec3 col, glm::vec3 pos) :Light(col, pos) {
	constantAttenuation = 1.0f;
	linearAttenuation = 0.09f;
	quadraticAttenuation = 0.032f;
}

PointLight::~PointLight() {

}

void PointLight::use(std::shared_ptr<Shader> shader, int num) {
	std::string number = std::to_string(num);

	shader->set<glm::vec3>("pointLights[" + number + "].position", getWorldPosition());

	shader->set<float>("pointLights[" + number + "].constant", constantAttenuation);
	shader->set<float>("pointLights[" + number + "].linear", linearAttenuation);
	shader->set<float>("pointLights[" + number + "].quadratic", quadraticAttenuation);

	shader->set<glm::vec3>("pointLights[" + number + "].ambient", ambient);
	shader->set<glm::vec3>("pointLights[" + number + "].diffuse", diffuse);
	shader->set<glm::vec3>("pointLights[" + number + "].specular", specular);
}

void PointLight::setAttenuation(float linear, float constant, float quad) {
	setLinear(linear);
	setConstant(constant);
	setQuadratic(quad);
}