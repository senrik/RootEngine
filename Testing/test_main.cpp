#include <stdio.h>
#include <stdlib.h>

typedef struct RootsObj {
	const float* verts;
	unsigned int vert_count;
	unsigned int* spans;
	unsigned int span_count;
	const char* v_shader, *f_shader;

} RootsObj;

// C:\Users\sswanson33\Documents\V22 Model\CV22 FBX\cv22_rig01_export06.fbx

int main(int argc, char* argv[]) {
	// create test rootsObj
	RootsObj diamond;
	diamond.vert_count = 40;
	diamond.verts = (float *) malloc(diamond.vert_count);

	diamond.span_count = 2;
	diamond.spans = (unsigned int*)malloc(diamond.span_count);
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
				
	}
	catch (...){

	}
	
	
	return 0;
}