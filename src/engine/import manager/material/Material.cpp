#include "Includes.h"

#include "Material.h"

Material::~Material() {

}

Material::Material(const std::shared_ptr<Shader> s):Component(COMPONENT_TYPE::MATERIAL), shader(s) {
	auto shaderUniforms = s->getUniforms();
	int textureCount = 0;
	// Fill out default values for shader if no config file provided
	for (auto uniform : shaderUniforms) {
		if (uniform.first.find("material") != std::string::npos) {
			auto it = uniform.first.find_first_of(".", uniform.first.find("material")) + 1;
			switch (uniform.second.first) {
			case GL_BOOL:
				config.add<bool>(uniform.first.substr(it), true);
				break;
			case GL_INT:
				config.add<int>(uniform.first.substr(it), 0);
				break;
			case GL_FLOAT:
				config.add<float>(uniform.first.substr(it), 1.0f);
				break;
			case GL_FLOAT_VEC3:
				config.add<glm::vec3>(uniform.first.substr(it), { 1.0f, 1.0f, 1.0f });
				break;
			case GL_FLOAT_MAT4:
				config.add<glm::mat4>(uniform.first.substr(it), glm::mat4());
				break;
			case GL_SAMPLER_2D:
				config.add<std::shared_ptr<Texture2D>>(uniform.first.substr(it), nullptr);
				textureMappings[uniform.first.substr(it)] = textureCount;
				textureCount++;
				break;
			default:
				LOG_WARN("MATERIAL::UNDEFINED TYPE {0} ADDED TO MATERIAL", uniform.second.first);
			}
		}
	}
}

void Material::useShader() {
	shader->use();
}

void Material::useMaterial(const MaterialConfig &con) {
	// Loop through internal config
		// if value is in other config, use that
		// else use default value

	for (auto materialUniform : config.properties) {
		if (con.properties.find(materialUniform.first) != con.properties.end()) {
			useConfigProperty(materialUniform.first, con.properties.at(materialUniform.first));
		}
		else {
			useConfigProperty(materialUniform.first, materialUniform.second);
		}
	}
}

void Material::useConfigProperty(const std::string &prop, const std::any &value) {
	if (value.type() == typeid(bool)) {
		setValue<bool>(prop, std::any_cast<bool>(value));
	}
	else if (value.type() == typeid(int)) {
		setValue<int>(prop, std::any_cast<int>(value));
	}
	else if (value.type() == typeid(float)) {
		setValue<float>(prop, std::any_cast<float>(value));
	}
	else if (value.type() == typeid(glm::vec3)) {
		setValue<glm::vec3>(prop, std::any_cast<glm::vec3>(value));
	}
	else if (value.type() == typeid(glm::mat4)) {
		setValue<glm::mat4>(prop, std::any_cast<glm::mat4>(value));
	}
	else if (value.type() == typeid(std::shared_ptr<Texture2D>)) {
		setValue<std::shared_ptr<Texture2D>>(prop, std::any_cast<std::shared_ptr<Texture2D>>(value));
	}
}