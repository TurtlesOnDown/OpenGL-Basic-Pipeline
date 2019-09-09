#pragma once

#include "Includes.h"

#include "model/Model.h"
#include "texture2D/Texture2D.h"
#include "shader/Shader.h"

class ImportManager {
public:
	ImportManager();
	~ImportManager();

	template<typename T>
	std::shared_ptr<T> load(std::string path) {
		LOG_WARN("IMPORTMANAGER::INCORRECT TYPE");
	}

	template<>
	std::shared_ptr<Texture2D> load(std::string path) {
		Path file(path);
		return textures2D.load(file);
	}

	template<>
	std::shared_ptr<Shader> load(std::string path) {
		Path file(path);
		return shaders.load(file);
	}

	template<>
	std::shared_ptr<Model> load(std::string path) {
		Path file(path);
		return models.load(file);
	}

	static ImportManager &getResourceManager() { return *resourceManager; }
	static void destroyManager() { resourceManager.reset(); }

private:
	static std::unique_ptr<ImportManager> resourceManager;

	ModelImporter models;
	Texture2DImporter textures2D;
	ShaderImporter shaders;
};