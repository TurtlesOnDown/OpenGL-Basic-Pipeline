#include "Includes.h"

#include "Model.h"
#include "../ImportManager.h"

Model::Model(Path file):Component(COMPONENT_TYPE::MODEL), path(file) {

}

Model::Model(const Model& m) : Component(COMPONENT_TYPE::MODEL), path(m.path) {
	meshes = m.meshes;
	mats = m.mats;
	individualVAO = m.individualVAO;
}

Model::~Model() {

}

ModelImporter::ModelImporter(ImportManager *imp):manager(imp) {

}

ModelImporter::~ModelImporter() {

}

std::shared_ptr<Model> ModelImporter::load(Path& p) {
	if (models.find(p.getPath()) != models.end()) {
		return copyModel(models[p.getPath()]);
	}
	else {
		models[p.getPath()] = loadModel(p);
		return copyModel(models[p.getPath()]);
	}
}

std::shared_ptr<Model> ModelImporter::loadModel(Path& p) {
	std::shared_ptr<Model> newModel(new Model(p));

	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(p.getPath(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		LOG_WARN("ERROR::ASSIMP::{0}", importer.GetErrorString());
		return std::shared_ptr<Model>(nullptr);
	}

	// process ASSIMP's root node recursively
	processNode(newModel, scene->mRootNode, scene);

	return newModel;
}

std::shared_ptr<Model> ModelImporter::copyModel(std::shared_ptr<Model> m) {
	std::shared_ptr<Model> newModel(new Model(*m));

	return newModel;
}

void ModelImporter::processNode(std::shared_ptr<Model> m, aiNode* node, const aiScene* scene) {
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMeshAndMaterial(m, mesh, scene);
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(m, node->mChildren[i], scene);
	}
}

void ModelImporter::processMeshAndMaterial(std::shared_ptr<Model> m, aiMesh* mesh, const aiScene* scene) {
	Material newMat = processMaterial(m, scene->mMaterials[mesh->mMaterialIndex]);
	std::shared_ptr<Mesh> newMesh = processMesh(m, mesh, scene);

	m->meshes.push_back(newMesh);
	m->mats.push_back({ m->meshes.size() - 1, newMat });
	
}

std::shared_ptr<Mesh> ModelImporter::processMesh(std::shared_ptr<Model> m, aiMesh* mesh, const aiScene* scene) {
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;
		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;
		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		// tangent
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.tangent = vector;
		// bitangent
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.bitangent = vector;
		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	std::shared_ptr<Mesh> ret(new Mesh(vertices, indices));
	if (m->individualVAO) ret->fillAndFormatVAO();
	return ret;
}

Material ModelImporter::processMaterial(std::shared_ptr<Model> m, aiMaterial* mat) {
	Material newMaterial;

	std::string matName = mat->GetName().C_Str();

	float shininess = 0.0f;
	if (AI_SUCCESS == mat->Get(AI_MATKEY_SHININESS, shininess)) {
		newMaterial.addFloat("shininess", shininess);
	}
	
	proccessTextures(m, newMaterial, mat, aiTextureType_DIFFUSE, "texture_diffuse");
	proccessTextures(m, newMaterial, mat, aiTextureType_SPECULAR, "texture_specular");
	proccessTextures(m, newMaterial, mat, aiTextureType_HEIGHT, "texture_normal");
	proccessTextures(m, newMaterial, mat, aiTextureType_AMBIENT, "texture_height");

	return newMaterial;
}

void ModelImporter::proccessTextures(std::shared_ptr<Model> m, Material& mat, aiMaterial* aiMat, aiTextureType type, std::string typeName) {
	for (unsigned int i = 0; i < aiMat->GetTextureCount(type); i++) {
		aiString str;
		aiMat->GetTexture(type, i, &str);

		std::shared_ptr<Texture2D> texture = manager->load<Texture2D>(m->path.getDirectory() + str.C_Str());
		texture->bind();
		texture->setWrappingParam(GL_REPEAT, GL_REPEAT);
		texture->setFilteringParam(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		texture->unbind();
		mat.addTexture2D(typeName + std::to_string(i), texture);
	}
}