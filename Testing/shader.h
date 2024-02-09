#ifndef SHADER_H
#define SHADER_H
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader {
public:
	unsigned int ID;
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void terminateShader();
};
#endif
