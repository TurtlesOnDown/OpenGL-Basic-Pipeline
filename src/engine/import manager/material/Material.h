#pragma once

#include "Includes.h"
#include <any>

#include "../../objects/Component.h"

#include "../shader/Shader.h"
#include "../texture2D/Texture2D.h"

// Material class to contain textures and parameters

struct MaterialConfig {
	std::map<std::string, std::any> properties;

	template<typename T>
	void add(const std::string &name, T value) {
		LOG_WARN("MATERIALCONFIG::INVALID TYPE ADDED");
	}

	template<>
	void add<std::shared_ptr<Texture2D>>(const std::string &name, std::shared_ptr<Texture2D> value) {
		properties[name] =  value;
	}

	template<>
	void add<bool>(const std::string &name, bool value) {
		properties[name] = value;
	}

	template<>
	void add<int>(const std::string &name, int value) {
		properties[name] = value;
	}

	template<>
	void add<float>(const std::string &name, float value) {
		properties[name] = value;
	}

	template<>
	void add<glm::vec3>(const std::string &name, glm::vec3 value) {
		properties[name] = value;
	}

	template<>
	void add<glm::mat4>(const std::string &name, glm::mat4 value) {
		properties[name] = value;
	}

};

class Material : public Component {
public:
	Material(const std::shared_ptr<Shader> s);
	~Material();

	void useShader();
	void useMaterial(const MaterialConfig &con);

	inline const std::shared_ptr<Shader> &getShader() { return shader; }

private:
	std::string matName;

	MaterialConfig config;
	std::map<std::string, int> textureMappings;
	const std::shared_ptr<Shader> shader;

	void useConfigProperty(const std::string &prop, const std::any &value);

	template<typename T>
	void setValue(std::string name, T value) {
		shader->set<T>("material." + name, value);
	}

	template<>
	void setValue<std::shared_ptr<Texture2D>>(std::string name, std::shared_ptr<Texture2D> value) {
		if (value == nullptr) return; // TODO: create default texture, or create better solution for null textures
		value->activateTexture(textureMappings[name]);
		shader->set<int>("material." + name, textureMappings[name]);

		value->bind();
	}
};
