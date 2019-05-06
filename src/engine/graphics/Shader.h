#include "../common/Includes.h"

#include "../common/Path.h"
#include "../objects/Component.h"

#ifndef SHADER
#define SHADER

class Shader : public Component {
public:
	Shader(Path& vertPath, Path& fragPath);
	~Shader();

	// Make sure glad has been initialized before loading any shaders.
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
	unsigned int ID;

	void compileShader(std::string vertPath, std::string fragPath);

	void checkCompileErrors(unsigned int shader, std::string type);

	Path path;
};
#endif // !SHADER

