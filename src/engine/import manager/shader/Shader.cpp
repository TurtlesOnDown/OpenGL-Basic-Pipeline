#include "Includes.h"

#include "Shader.h"

#include <fstream>
#include <sstream>

Shader::Shader(Path shaderfile) :Component(COMPONENT_TYPE::SHADER),path(shaderfile) {
	
}

Shader::~Shader() {

}

void Shader::use() {
	glUseProgram(ID);
}


ShaderImporter::ShaderImporter(ImportManager *imp):manager(imp) {

}

ShaderImporter::~ShaderImporter() {

}

std::shared_ptr<Shader> ShaderImporter::load(Path& p) {
	if (shaders.find(p.getPath()) != shaders.end()) {
		return shaders[p.getPath()];
	}

	std::shared_ptr<Shader> ret = std::shared_ptr<Shader>(new Shader(p));
	shaders[p.getPath()] = ret;
	importShader(ret);
	return ret;
}

void ShaderImporter::importShader(std::shared_ptr<Shader> shader) {
	std::ifstream lshaderFile;
	std::string vertexPath;
	std::string fragmentPath;

	try {
		// open file
		lshaderFile.open(shader->path.getPath());
		// get vertex path
		std::getline(lshaderFile, vertexPath);
		// get fragment path
		std::getline(lshaderFile, fragmentPath);
		// close file
		lshaderFile.close();
	}
	catch (std::ifstream::failure e)
	{
		LOG_WARN("SHADER::UNABLE TO LOAD SHAD FILE");
		return;
	}

	compileShader(shader, shader->path.getDirectory() + vertexPath, shader->path.getDirectory() + fragmentPath);
}

void ShaderImporter::compileShader(std::shared_ptr<Shader> shader, std::string vertPath, std::string fragPath) {
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	std::string vertexCode;
	std::string fragmentCode;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertPath);
		fShaderFile.open(fragPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		LOG_WARN("SHADER::UNABLE TO READ VSHADER/FSHADER");
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	shader->ID = glCreateProgram();
	glAttachShader(shader->ID, vertex);
	glAttachShader(shader->ID, fragment);
	glLinkProgram(shader->ID);
	checkCompileErrors(shader->ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void ShaderImporter::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			LOG_ERROR("SHADER::COMPILE ERROR::{0}::{1}", type, infoLog);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			LOG_ERROR("SHADER::LINKING ERROR::{0}::{1}", type, infoLog);
		}
	}
}