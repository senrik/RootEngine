#ifndef ROOTS_OBJECT_H
#define ROOTS_OBJECT_H
//#include <Shader/shader.h>
class RootsObj {
public:
	RootsObj();
	RootsObj(const RootsObj&);
	~RootsObj();
	void SerializeRootsObj();
private:
	float* verts;
	unsigned int vert_count;
	unsigned int* spans;
	unsigned int span_count;

	unsigned int t_width, t_height;
	unsigned char* textureData;
};
#endif