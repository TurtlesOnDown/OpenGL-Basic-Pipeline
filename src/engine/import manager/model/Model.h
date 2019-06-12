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
	Model(Path& file);
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
};

#endif