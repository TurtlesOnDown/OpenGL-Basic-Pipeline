#pragma once

#include "../../objects/PObject.h"
#include "../../import manager/shader/Shader.h"

class Light : public PObject {
public:
	Light(glm::vec3 color = {1.0f, 1.0f, 1.0f}, glm::vec3 pos = { 0.0f , 0.0f, 0.0f });
	virtual ~Light();

	virtual void use(std::shared_ptr<Shader> shader, int num) = 0;

	inline void setColor(glm::vec3 col) { color = col; }
	inline void setAmbient(glm::vec3 col) { ambient = col; }
	inline void setDiffuse(glm::vec3 col) { diffuse = col; }
	inline void setSpecular(glm::vec3 col) { specular = col; }
	inline glm::vec3 &getColor() { return color; }
	inline glm::vec3 &getAmbient() { return ambient; }
	inline glm::vec3 &getDiffuse() { return diffuse; }
	inline glm::vec3 &getSpecular() { return specular; }
protected:
	glm::vec3 color;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
