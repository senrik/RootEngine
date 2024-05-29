#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H
#include "shader.h"
typedef struct RootsObj {
	float* verts;
	unsigned int vert_count;
	unsigned int* spans;
	unsigned int span_count;
	Shader shader;
	unsigned int t_width, t_height;
	unsigned char* textureData;
} RootsObj;
#endif