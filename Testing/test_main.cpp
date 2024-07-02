#include <stdio.h>
#include <data_types.h>
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


int main(int argc, char* argv[]) {

	
	printf_s("Default Vert Shader:\n%s", DEFAULT_VERT_CODE);
	//RenderCache* cache = (RenderCache*)malloc(sizeof(RenderCache));
	//RenderCache_Init(cache);
	
	return 0;
}

/*
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
*/