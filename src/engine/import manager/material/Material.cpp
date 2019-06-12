#include "Includes.h"

#include "Material.h"

Material::Material():Component(COMPONENT_TYPE::MATERIAL) {

}

Material::~Material() {

}

Material Material::operator=(const Material& m) {
	textures2D = m.textures2D; 
	return *this;
}

void Material::addTexture2D(std::string name, const std::shared_ptr<Texture2D> t) {
	textures2D[name] = t;
}

void Material::addFloat(std::string name, float value) {
	floatValues[name] = value;
}

void Material::useMaterial(const std::shared_ptr<Shader> shader) {
	shader->use();

	int count = 0;
	for (auto texture : textures2D) {
		texture.second->activateTexture(count);
		shader->setInt(texture.first, count);
		count++;

		texture.second->bind();
	}

	for (auto x : floatValues) {
		shader->setFloat(x.first, x.second);
	}
	
}