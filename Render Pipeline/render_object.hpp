#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
	// buffer objects
	unsigned int VBO, VAO, EBO, texture;
	// collection of raw data for vertices
	float* verticies;
	// size of the vertices collection, in bytes
	unsigned int vertSize;
	// number of data points in the raw data
	unsigned int vertCount;
	// collection of indices if an element buffer is used
	unsigned int* indices;
	// size of the indices collection, in bytes
	unsigned int indicesSize;
	// number of indices
	unsigned int indicesCount;
	// collections of spans
	unsigned int* spans;
	// number of spans
	unsigned int spanCount;
	// the summation of all the spans
	unsigned int totalSpan;
	// texture data points
	int t_width, t_height, nrChannels;
	// raw texture data
	unsigned char* textureData;
	// shader
	Shader objShader;
	// world space coordinates
	float xPos, yPos, zPos;
	// world scale values
	float xScale, yScale, zScale;
	glm::quat rotation;
};

void RenderObj_Draw(RenderObj*);
void RenderObj_Init(RenderObj*);
void RenderObj_Terminate(RenderObj*);
#endif