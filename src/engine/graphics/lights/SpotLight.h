#pragma once

#include "PointLight.h"

class SpotLight : public PointLight {
public:
	SpotLight(glm::vec3 color = { 1.0f, 1.0f, 1.0f }, glm::vec3 pos = { 0.0f , 0.0f, 0.0f });
	~SpotLight();

	virtual void use(std::shared_ptr<Shader> shader, int num) override;

	inline virtual void setCutOff(float value) { cutOff = value; }
	inline virtual void setOuterCutOff(float value) { outerCutOff = value; }
	inline virtual float getCutOff() { return cutOff; }
	inline virtual float getOuterCutOff() { return outerCutOff; }

protected:
	float cutOff;
	float outerCutOff;
};