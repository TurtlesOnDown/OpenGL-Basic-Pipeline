#pragma once

#include "Light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight(glm::vec3 color = { 1.0f, 1.0f, 1.0f }, glm::vec3 pos = { 0.0f , 0.0f, 0.0f });
	~DirectionalLight();

	virtual void use(std::shared_ptr<Shader> shader, int num) override;

private:
};
