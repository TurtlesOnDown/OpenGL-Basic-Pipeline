#include "Includes.h"

#include "Light.h"

Light::Light(glm::vec3 col, glm::vec3 pos):PObject(pos), color(col) {
	ambient = color * 0.2f;
	diffuse = color;
	specular = color;
}

Light::~Light() {

}
