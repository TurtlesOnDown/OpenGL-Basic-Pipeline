#include "Includes.h"

#include "../../common/Path.h"
#include "../../objects/Component.h"

#ifndef SHADERCLASS
#define SHADERCLASS

// OpenGL Shader class

class Shader : public Component {
public:
	Shader(Path& shaderfile);
	~Shader();

	// Make sure glad has been initialized before loading any shaders.
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;


private:
	unsigned int ID;

	Path path;

	friend class ShaderImporter;
};

class ImportManager;

class ShaderImporter {
public:
	ShaderImporter(ImportManager *imp);
	~ShaderImporter();

	std::shared_ptr<Shader> load(Path& p);
private:
	std::map<std::string, std::shared_ptr<Shader>> shaders;
	ImportManager *manager;

	void importShader(std::shared_ptr<Shader> shader);
	void compileShader(std::shared_ptr<Shader> shader, std::string vertPath, std::string fragPath);
	void checkCompileErrors(unsigned int shader, std::string type);
};
#endif // !SHADER

