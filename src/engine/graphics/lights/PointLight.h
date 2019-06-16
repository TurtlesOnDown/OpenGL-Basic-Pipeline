#pragma once

#include "Light.h"

class PointLight : public Light {
public:
	PointLight(glm::vec3 color = { 1.0f, 1.0f, 1.0f }, glm::vec3 pos = { 0.0f , 0.0f, 0.0f });
	~PointLight();

	virtual void use(std::shared_ptr<Shader> shader, int num) override;

	virtual void setAttenuation(float linear, float constant, float quad);

	inline virtual void setConstant(float value) { constantAttenuation = value; }
	inline virtual void setLinear(float value) { linearAttenuation = value; }
	inline virtual void setQuadratic(float value) { quadraticAttenuation = value; }
	inline virtual float getConstant() { return constantAttenuation; }
	inline virtual float getAttenuation() { return linearAttenuation; }
	inline virtual float getQuadratic() { return quadraticAttenuation; }

protected:
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};
