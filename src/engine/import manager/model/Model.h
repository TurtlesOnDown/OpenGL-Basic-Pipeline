#include "Includes.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../common/Path.h"
#include "../material/Material.h"
#include "Mesh.h"

#ifndef MODELCLASS
#define MODELCLASS

class Model : public Component {
public:
	Model(Path file);
	Model(const Model& m);
	~Model();

	void setIndividualVAO(bool a) { individualVAO = a; }

	void setMaterial(unsigned int index, Material m) { mats[index].second = m; } // clean this up

	const std::vector<std::pair<unsigned int, Material>> &getMaterials() const { return mats; }
	const std::vector<std::shared_ptr<Mesh>>& getMeshes() const { return meshes; }
private:
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<std::pair<unsigned int, Material>> mats;
	Path path;
	bool individualVAO = true;

	friend class ModelImporter;
};

class ImportManager;

class ModelImporter {
public:
	ModelImporter(ImportManager *imp);
	~ModelImporter();

	std::shared_ptr<Model> load(Path& p);

private:
	std::map<std::string, std::shared_ptr<Model>> models;
	ImportManager *manager;

	std::shared_ptr<Model> loadModel(Path& p);
	void processNode(std::shared_ptr<Model> m, aiNode* node, const aiScene* scene);
	void processMeshAndMaterial(std::shared_ptr<Model> m, aiMesh* mesh, const aiScene* scene);
	std::shared_ptr<Mesh> processMesh(std::shared_ptr<Model> m, aiMesh* mesh, const aiScene* scene);
	Material processMaterial(std::shared_ptr<Model> m, aiMaterial* mat);
	void proccessTextures(std::shared_ptr<Model> m, Material& mat, aiMaterial* aiMat, aiTextureType type, std::string typeName);

	std::shared_ptr<Model> copyModel(std::shared_ptr<Model> m);

	template<typename T>
	void getMaterialProperty(Material &newMaterial, aiMaterial *mat, const char *pKey, unsigned int type, unsigned int idx, std::string matProperty, T defaultValue) {
		T value;
		if (AI_SUCCESS == mat->Get(pKey, type, idx, value)) {
			newMaterial.add<T>(matProperty, value);
		}
		else {
			newMaterial.add<T>(matProperty, defaultValue);
		}
	}

	template<>
	void getMaterialProperty<glm::vec3>(Material &newMaterial, aiMaterial *mat, const char *pKey, unsigned int type, unsigned int idx, std::string matProperty, glm::vec3 defaultValue) {
		aiColor3D color;
		glm::vec3 value;
		if (AI_SUCCESS == mat->Get(pKey, type, idx, color)) {
			value = { color.r, color.g, color.b };
			newMaterial.add<glm::vec3>(matProperty, value);
		}
		else {
			newMaterial.add<glm::vec3>(matProperty, defaultValue);
		}
	}
};

#endif