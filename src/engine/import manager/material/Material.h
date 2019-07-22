#pragma once

#include "Includes.h"

#include "../../objects/Component.h"

#include "../shader/Shader.h"
#include "../texture2D/Texture2D.h"

// Material class to contain textures and parameters

class Material : public Component {
public:
	Material();
	Material(std::string name);
	~Material();
	Material operator=(const Material& m);

	template<typename T>
	void add(const std::string &name, T value) {
		LOG_WARN("MATERIAL::INVALID TYPE ADDED");
	}

	template<>
	void add<std::shared_ptr<Texture2D>>(const std::string &name, std::shared_ptr<Texture2D> value) {
		textures2D[name] = value;
	}

	template<>
	void add<bool>(const std::string &name, bool value) {
		boolValues[name] = value;
	}

	template<>
	void add<int>(const std::string &name, int value) {
		intValues[name] = value;
	}

	template<>
	void add<float>(const std::string &name, float value) {
		floatValues[name] = value;
	}

	template<>
	void add<glm::vec3>(const std::string &name, glm::vec3 value) {
		vec3Values[name] = value;
	}

	template<>
	void add<glm::mat4>(const std::string &name, glm::mat4 value) {
		mat4Values[name] = value;
	}

	void useMaterial(const std::shared_ptr<Shader> s);

private:
	std::string matName;
	std::map<std::string, std::shared_ptr<Texture2D>> textures2D;
	std::map<std::string, bool> boolValues;
	std::map<std::string, int> intValues;
	std::map<std::string, float> floatValues;
	std::map<std::string, glm::vec3> vec3Values;
	std::map<std::string, glm::mat4> mat4Values;

	template<typename T>
	void setValues(const std::shared_ptr<Shader> shader, std::map<std::string, T> values) {
		for (auto x : values) {
			shader->set<T>("material." + x.first, x.second);
		}
	}

	template<>
	void setValues<std::shared_ptr<Texture2D>>(const std::shared_ptr<Shader> shader, std::map<std::string, std::shared_ptr<Texture2D>> values) {
		int count = 0;
		for (auto texture : values) {
			texture.second->activateTexture(count);
			shader->set<int>("material." + texture.first, count);
			count++;

			texture.second->bind();
		}
	}
};
