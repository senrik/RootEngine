#include <stdio.h>
#include <stdlib.h>
#include <RootsObj.hpp>


// C:\Users\sswanson33\Documents\V22 Model\CV22 FBX\cv22_rig01_export06.fbx

float diamondVerts[] = {
	// position			   // texcoords
	0.0f,  0.5f,  0.0f,    0.0f,  1.0f, //  0,  1,  2,  3,  4,
   -0.5f,  0.0f,  0.0f,    1.0f, -1.0f, //  5,  6,  7,  8,  9,
	0.0f,  0.0f, -0.5f,   -1.0f,  1.0f, // 10, 11, 12, 13, 14,

	0.0f, -0.5f,  0.0f,    0.0f, -1.0f, // 
   -0.5f,  0.0f,  0.0f,    1.0f, -1.0f,
	0.0f,  0.0f, -0.5f,   -1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,    0.0f,  1.0f,
	0.5f,  0.0f,  0.0f,    1.0f, -1.0f,
	0.0f,  0.0f, -0.5f,   -1.0f,  1.0f,

	0.0f, -0.5f,  0.0f,    0.0f, -1.0f,
	0.5f,  0.0f,  0.0f,    1.0f, -1.0f,
	0.0f,  0.0f, -0.5f,   -1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,    0.0f,  1.0f,
   -0.5f,  0.0f,  0.0f,    1.0f, -1.0f,
	0.0f,  0.0f,  0.5f,   -1.0f, -1.0f,

	0.0f, -0.5f,  0.0f,    0.0f, -1.0f,
   -0.5f,  0.0f,  0.0f,    1.0f, -1.0f,
	0.0f,  0.0f,  0.5f,   -1.0f, -1.0f,

	0.0f,  0.5f,  0.0f,    0.0f,  1.0f,
	0.5f,  0.0f,  0.0f,    1.0f, -1.0f,
	0.0f,  0.0f,  0.5f,   -1.0f, -1.0f,

	0.0f, -0.5f,  0.0f,    0.0f, -1.0f,
	0.5f,  0.0f,  0.0f,    1.0f, -1.0f,
	0.0f,  0.0f,  0.5f,   -1.0f, -1.0f,
};
void WriteModelFile(const RootsObj&, const char*);
void ReadModelFile(RootsObj&, const char*);

int main(int argc, char* argv[]) {
	// create test rootsObj
	RootsObj diamond, diamond2;
	diamond.vert_count = 120;
	diamond.verts = (float *) malloc(diamond.vert_count*sizeof(float));
	for (int i = 0; i < diamond.vert_count; i++) {
		diamond.verts[i] = diamondVerts[i];
	}

	diamond.span_count = 2;
	diamond.spans = (unsigned int*)malloc(diamond.span_count*sizeof(unsigned int));
	diamond.spans[0] = 3;
	diamond.spans[1] = 2;
	// Shaders are static for now, but should have their own files that are read and added to the binary file.
	diamond.shader = Shader("v_shader.vertshader", "f_shader.fragshader");
	
	WriteModelFile(diamond, "diamondObj.bin");

	ReadModelFile(diamond2, "diamondObj.bin");
		
	
	return 0;
}

void WriteModelFile(const RootsObj& obj,  const char* filePath) {
	// write binary
	FILE* ptr_myFile;
	fopen_s(&ptr_myFile, filePath, "wb");
	if (!ptr_myFile) {
		printf("Unable to open file: %s", filePath);
	}
	else {
		fwrite(&obj, sizeof(RootsObj), 1, ptr_myFile);

		fclose(ptr_myFile);
	}
	
}

void ReadModelFile(RootsObj& obj, const char* filePath) {
	// read binary
	FILE* ptr_myFile;
	fopen_s(&ptr_myFile, filePath, "rb");
	if (!ptr_myFile) {
		printf("Unable to open file: %s", "diamondObj.bin");
	}
	else {
		fread_s(&obj, sizeof(RootsObj) * 2, sizeof(RootsObj), 1, ptr_myFile);
		fclose(ptr_myFile);
	}	
}