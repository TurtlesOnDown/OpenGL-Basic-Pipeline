#pragma once

#include "engine/objects/PObject.h"

class ExampleObject : public PObject {
public:
	ExampleObject(glm::vec3 pos = { 0.0f, 0.0f, 0.0f }, glm::vec3 s = { 1.0f, 1.0f, 1.0f });
	~ExampleObject();

	virtual void onUpdate() override;
	virtual void onEvent(Event &e) override;

private:
	float counter = 0;
};