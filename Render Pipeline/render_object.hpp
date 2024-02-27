#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <stb_image.h>
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

typedef struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
} Vertex;

typedef struct Texture {
	int t_width, t_height, nrChannels;
	
	unsigned char* textureData;
} Texture;

typedef struct Mesh {
	Vertex* vertices;
	unsigned int vertCount;
	unsigned int vertSize;

	unsigned int* indices;
	unsigned int indicesCount;
	unsigned int indicesSize;

	Texture* textures;
	unsigned int textureCount;
	unsigned int textureSize;
} Mesh;

typedef struct RenderObj {
public:
	// buffer objects
	unsigned int VBO, VAO, EBO, texture;
	// collection of raw data for vertices
	float* rawVertices;
	// size of the vertices collection, in bytes
	unsigned int rawVertSize;
	// number of data points in the raw data
	unsigned int rawVertCount;
	//Vertex* vertices;
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
	// mesh structs
	Mesh mesh;
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
} RenderObj;

void Texture_Init(Texture*, const char*);
void Texture_Terminate(Texture*);

void Mesh_Init(Mesh*);
void Mesh_Draw(Mesh*);
void Mesh_Terminate(Mesh*);

void RenderObj_Draw(RenderObj*);
void RenderObj_Init(RenderObj*);
void RenderObj_Terminate(RenderObj*);


#endif