#include <stdio.h>
#include <stdlib.h>

typedef struct RootsObj {
	float* verts;
	unsigned int vert_count;
	unsigned int* spans;
	unsigned int span_count;
	const char* v_shader, *f_shader;
	

} RootsObj;

// C:\Users\sswanson33\Documents\V22 Model\CV22 FBX\cv22_rig01_export06.fbx

float diamondVerts[] = {
	// position			// texcoords
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
	diamond.v_shader = "#version 330 core\n"

		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec2 aTexCoord;\n"

		"out vec2 TexCoord;\n"

		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"

		"void main() {\n"
		"gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
		"TexCoord = aTexCoord;\n"
		"}\0";
	diamond.f_shader = "#version 330 core\n"
		"out vec4 FragColor;\n"

		"in vec2 TexCoord;\n"

		"uniform sampler2D texture1;\n"
		"uniform sampler2D texture2;\n"

		"void main() {\n"
		"FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
		"}\0";
	try{
		// write binary
		FILE* ptr_myFile;
		fopen_s(&ptr_myFile, "diamondObj.bin", "wb");
		if (!ptr_myFile) {
			printf("Unable to open file: %s", "diamondObj.bin");
			return -1;
		}
		fwrite(&diamond, sizeof(RootsObj), 1, ptr_myFile);

		fclose(ptr_myFile);
		// read binary
		fopen_s(&ptr_myFile, "diamondObj.bin", "rb");
		if (!ptr_myFile) {
			printf("Unable to open file: %s", "diamondObj.bin");
			return -1;
		}
		fread_s(&diamond2, sizeof(RootsObj)*2, sizeof(RootsObj), 1, ptr_myFile);
		fclose(ptr_myFile);

		// Check to see if the spans are vertex recording work
		//position span
		unsigned int span = diamond2.spans[0] + diamond2.spans[1];
		unsigned int formatCount = 0;
		printf("Vertex Count: %d\nSpan: %d\n", diamond2.vert_count, span);
		for (int i = 0; i < diamond2.vert_count; i++) {			
			// print out all position verts:
			if (i % span < diamond2.spans[0]) {
				printf("%.1F ", diamond2.verts[i]);
				
			}
			if (i % span == diamond2.spans[0]) {
				printf("\n");
			}

		}
	}
	catch (...){

	}
	
	
	return 0;
}