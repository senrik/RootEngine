#include <stdio.h>
#include <roots_math.h>
#include <glad/glad.h>
#include <glfw3.h>
// C:\Users\sswanson33\Documents\V22 Model\CV22 FBX\cv22_rig01_export06.fbx


int main(int argc, char* argv[]) {

	printf_s("Hello, world!");
	rt_vec2* _vec = (rt_vec2*)malloc(sizeof(rt_vec2));
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