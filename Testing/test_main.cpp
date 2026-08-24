#include <iostream>
#include <roots_math.h>
#include <asset_io.h>
#include <glad.h>
#include <GLFW/glfw3.h>
// C:\Users\sswanson33\Documents\V22 Model\CV22 FBX\cv22_rig01_export06.fbx


int main(int argc, char* argv[]) {

	std::cout << "Hello, world!" << std::endl;
	rt_mat4 identity;
	mat4_init(&identity, 1);
	if (!glfwInit()) {

	}
	auto window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		//
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window)) {

	}
	glfwDestroyWindow(window);
	glfwTerminate();
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