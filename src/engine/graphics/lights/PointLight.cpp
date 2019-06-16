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

	shader->setVec3("pointLights[" + number + "].position", position);

	shader->setFloat("pointLights[" + number + "].constant", constantAttenuation);
	shader->setFloat("pointLights[" + number + "].linear", linearAttenuation);
	shader->setFloat("pointLights[" + number + "].quadratic", quadraticAttenuation);

	shader->setVec3("pointLights[" + number + "].ambient", ambient);
	shader->setVec3("pointLights[" + number + "].diffuse", diffuse);
	shader->setVec3("pointLights[" + number + "].specular", specular);
}

void PointLight::setAttenuation(float linear, float constant, float quad) {
	setLinear(linear);
	setConstant(constant);
	setQuadratic(quad);
}