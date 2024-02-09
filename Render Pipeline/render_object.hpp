#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader {
public:
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void terminateShader();
private:
	unsigned int ID;
};


class RenderObj {
public:
	unsigned int VBO, VAO, texture;
	float* verticies;
	unsigned int vertSize;
	unsigned int vertCount;
	unsigned int* spans;
	unsigned int spanCount;
	unsigned int totalSpan;
	int t_width, t_height, nrChannels;
	unsigned char* textureData;
	Shader objShader;
	// world space coordinates
	float xPos, yPos, zPos;
};

void RenderObj_Draw(RenderObj*);
void RenderObj_Init(RenderObj*);
void RenderObj_Terminate(RenderObj*);

#endif