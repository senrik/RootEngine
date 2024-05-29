#include "shader.h"

Shader::Shader() {
	ID = -1;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	ID = 0;
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
	}
	const char* vShaderCode = vertexCode.c_str();
	printf("Vertex Shader: \n%s\n", vShaderCode);
	const char* fShaderCode = fragmentCode.c_str();
	printf("Fragment Shader: \n%s\n", fShaderCode);
}

void Shader::use() {
	
}

void Shader::terminateShader() {

}