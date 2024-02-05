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

typedef enum FormatFlags {
	VERTEX_POS = (1<<0), //0
	VERTEX_COLOR = (1<<1), //2
	TEX_COORD = (1<<2) //4
} FormatFlags;

class RenderObj {
public:
	RenderObj();
	void Draw();
private:
	std::vector<float> verts;
	Shader objShader;
	unsigned char* textureData;
};

RenderObj::RenderObj() {
	
}

#endif