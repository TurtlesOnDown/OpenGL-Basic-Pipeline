#pragma once

#include "model/Model.h"
#include "texture2D/Texture2D.h"
#include "shader/Shader.h"

class ImportManager {
public:
	ImportManager();
	~ImportManager();

	template<typename T>
	std::shared_ptr<T> load(Path file) {
		std::cout << "IMPORTMANAGER::INCORRECT TYPE" << std::endl;
	}

	template<>
	std::shared_ptr<Texture2D> load(Path file) {
		return textures2D.load(file);
	}

	template<>
	std::shared_ptr<Shader> load(Path file) {
		
		return shaders.load(file);
	}

	template<>
	std::shared_ptr<Model> load(Path file) {
		return models.load(file);
	}

private:
	ModelImporter models;
	Texture2DImporter textures2D;
	ShaderImporter shaders;
};