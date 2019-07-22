#include "Includes.h"

#include "../../common/Path.h"
#include "../../objects/Component.h"

#ifndef SHADERCLASS
#define SHADERCLASS

// OpenGL Shader class

class Shader : public Component {
public:
	Shader(Path shaderfile);
	~Shader();

	// Make sure glad has been initialized before loading any shaders.
	void use();

	template<typename T>
	void set(const std::string &name, T value) {
		LOG_WARN("SHADER::INVALID TYPE SET");
	}

	template<>
	void set<bool>(const std::string &name, bool value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	template<>
	void set<int>(const std::string &name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	template<>
	void set<float>(const std::string &name, float value) {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	template<>
	void set<glm::vec3>(const std::string &name, glm::vec3 value) {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	template<>
	void set<glm::mat4>(const std::string &name, glm::mat4 value) {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

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

