#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H
#include <vector>
#include "shader.hpp"
// RenderObject
// - verticies
// - reference to texture (if none, one will be provided)
// - shader

// classes used to render objects in OpenGL
// every object at least has a array of verticies
// has an associated shader
// rendered object -- all are textured, use a debug texture to apply to the object if it doesn't have a texture
// flags for how the verticies are arranged

typedef struct ImageData {
	int width, height, nrChannels;
	const unsigned char* textureData;
} ImgData;

typedef struct RenderObj {
	float* verts;
	unsigned int vert_count;
	unsigned int* spans;
	unsigned int span_count;
	const char* v_shader, * f_shader;
	ImgData textureData;
	// position data is world-space
	float xPos, yPos, zPos;

} RenderObj;

#endif