#include "Includes.h"

#include "Material.h"

Material::Material():Component(COMPONENT_TYPE::MATERIAL) {

}

Material::Material(std::string name):Component(COMPONENT_TYPE::MATERIAL), matName(name) {

}

Material::~Material() {

}

Material Material::operator=(const Material& m) {
	matName = m.matName;
	textures2D = m.textures2D; 
	vec3Values = m.vec3Values;
	boolValues = m.boolValues;
	intValues = m.intValues;
	floatValues = m.floatValues;
	mat4Values = m.mat4Values;
	return *this;
}

void Material::useMaterial(const std::shared_ptr<Shader> shader) {
	shader->use();

	setValues<std::shared_ptr<Texture2D>>(shader, textures2D);
	setValues<bool>(shader, boolValues);
	setValues<int>(shader, intValues);
	setValues<float>(shader, floatValues);
	setValues<glm::vec3>(shader, vec3Values);
	setValues<glm::mat4>(shader, mat4Values);

	GLGET_ERROR();
}