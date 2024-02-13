#include <stdio.h>
#include <math.h>
#include <vector>
#include "render_object.hpp"
#include "Camera.hpp"
#include <glad/glad.h> //manages function pointers for OpenGL
#include <GLFW/glfw3.h> // Abstraction layer for targeting multiple systems with OpenGL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ufbx.h>
#include <stb_image.h> // image loader



#pragma region Callback functions Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#pragma endregion



void processInput(GLFWwindow* window, float deltaTime);

// Render Pipeline boiler plate code
int RenderPipeline_BP();

void RenderCache_Add(const RenderObj*);
void RenderCache_Draw(glm::mat4, glm::mat4,float);
void RenderCache_Clear();
void RenderCache_AddMesh(const char*, ufbx_load_opts*, ufbx_error*);
#define SCRN_WIDTH 800
#define SCRN_HEIGHT 600
#define RENDER_CACHE_SIZE 200

static RenderObj* renderCache;
static unsigned int cacheSize = 0;
static GLFWwindow* window;
float rotationSpeed = 30.0f;

int main(int argc, char* argv[]) {
  
#pragma region Boiler Plate
	RenderPipeline_BP();
#pragma endregion

	renderCache = (RenderObj*)malloc(sizeof(RenderObj) * RENDER_CACHE_SIZE);
#pragma region Cube
	float cubeVerts[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0 - bottom left
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1 - bottom right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2 - top right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3 - top left

		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // 4 - bottom left
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // 5 - bottom right
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // 6 - top right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 7 - top left

	};
	unsigned int cubeIndices[] = {
		3, 1, 0,
		1, 2, 3,

		7, 4, 5,
		5, 6, 7,

		7, 3, 2,
		2, 6, 7,

		4, 0, 1,
		1, 5, 4,

		2, 1, 5,
		5, 6, 2,

		3, 0, 4,
		4, 7, 3

	};
	RenderObj cube;
	cube.vertCount = sizeof(cubeVerts)/sizeof(float);
	cube.vertSize = sizeof(cubeVerts);
	cube.verticies = (float*)malloc(sizeof(float) * cube.vertCount);
	for (int i = 0; i < cube.vertCount; i++) {
		cube.verticies[i] = cubeVerts[i];
	}
	cube.indicesCount = sizeof(cubeIndices)/sizeof(unsigned int);
	cube.indicesSize = sizeof(cubeIndices);
	cube.indices = (unsigned int*)malloc(sizeof(unsigned int) * cube.indicesCount);
	for (int i = 0; i < cube.indicesCount; i++) {
		cube.indices[i] = cubeIndices[i];
	}
	cube.spanCount = 2;
	cube.spans = (unsigned*)malloc((sizeof(unsigned int) * cube.spanCount));
	cube.spans[0] = 3;
	cube.spans[1] = 2;
	cube.totalSpan = 5;
	cube.objShader = Shader("v_shader.vertshader", "f_shader.fragshader");
	cube.textureData = stbi_load("container.jpg", &cube.t_width, &cube.t_height, &cube.nrChannels, 0);
	cube.xPos = 1.0f;
	cube.yPos = -0.5f;
	cube.zPos = 0.0f;
	RenderObj_Init(&cube);
#pragma endregion
	RenderCache_Add(&cube);
#pragma region Diamond
	float diamondVerts[] = {
		 // position			// texcoords
		 0.0f,  0.5f,  0.0f,    0.5f,  0.5f,
		-0.5f,  0.0f,  0.0f,   -1.0f,  0.0f,
		 0.0f,  0.0f, -0.5f,    1.0f,  0.0f,

		 0.0f, -0.5f,  0.0f,    0.5f,  0.5f,
		-0.5f,  0.0f,  0.0f,   -1.0f,  0.0f,
		 0.0f,  0.0f, -0.5f,    1.0f,  0.0f,

		 0.0f,  0.5f,  0.0f,    0.5f,  0.5f,
		 0.5f,  0.0f,  0.0f,   -1.0f,  0.0f,
		 0.0f,  0.0f, -0.5f,    1.0f,  0.0f,

		 0.0f, -0.5f,  0.0f,    0.5f,  0.5f,
		 0.5f,  0.0f,  0.0f,   -1.0f,  0.0f, 
		 0.0f,  0.0f, -0.5f,    1.0f,  0.0f,

		 0.0f,  0.5f,  0.0f,    0.5f,  0.5f,
		-0.5f,  0.0f,  0.0f,   -1.0f,  0.0f,
		 0.0f,  0.0f,  0.5f,    1.0f,  0.0f,

		 0.0f, -0.5f,  0.0f,    0.5f,  0.5f,
		-0.5f,  0.0f,  0.0f,   -1.0f,  0.0f,
		 0.0f,  0.0f,  0.5f,    1.0f,  0.0f,
		
		 0.0f,  0.5f,  0.0f,    0.5f,  0.5f,
		 0.5f,  0.0f,  0.0f,   -1.0f,  0.0f,
		 0.0f,  0.0f,  0.5f,    1.0f,  0.0f,

		 0.0f, -0.5f,  0.0f,    0.5f,  0.5f,
		 0.5f,  0.0f,  0.0f,   -1.0f,  0.0f,
		 0.0f,  0.0f,  0.5f,    1.0f,  0.0f,
	};
	RenderObj diamond;
	diamond.vertCount = sizeof(diamondVerts)/sizeof(float);
	diamond.verticies = (float*)malloc(sizeof(float) * diamond.vertCount);
	for (int i = 0; i < diamond.vertCount; i++) {
		diamond.verticies[i] = diamondVerts[i];
	}
	diamond.vertSize = sizeof(diamondVerts);
	diamond.spanCount = 2; // two different attributes to the verticies
	diamond.spans = (unsigned int*)malloc((sizeof(unsigned int) * diamond.spanCount));
	diamond.spans[0] = 3;
	diamond.spans[1] = 2;
	diamond.totalSpan = 5;
	diamond.objShader = Shader("v_shader.vertshader", "f_shader.fragshader");	
	diamond.textureData = stbi_load("container.jpg", &diamond.t_width, &diamond.t_height, &diamond.nrChannels, 0);
	diamond.xPos = -1.0f;
	diamond.yPos = 0.5f;
	diamond.zPos = 0.0f;

	RenderObj_Init(&diamond);
#pragma endregion
	RenderCache_Add(&diamond);
	
#pragma region V22
	ufbx_load_opts opts = { 0 };
	ufbx_error fbx_error;
	RenderCache_AddMesh("cv22_rig01_export07.fbx", &opts, &fbx_error);
#pragma endregion
	
	float deltaTime = 0;
	while (!glfwWindowShouldClose(window)) {
		float timeValue = (float)glfwGetTime();
		deltaTime = timeValue - deltaTime;
		// INPUT
		processInput(window, deltaTime);


		// RENDER CALLS
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// set the camera space
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		// set the perspective matrix
		proj = glm::perspective(glm::radians(45.0f), (float)SCRN_WIDTH / (float)SCRN_HEIGHT, 0.01f, 1000.0f);

		RenderCache_Draw(view, proj, timeValue);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		// Update delta time
		deltaTime = timeValue;
	}
	RenderCache_Clear();

	glfwTerminate();
	return 0;
}

#pragma region Callback functions Implimentations
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
#pragma endregion

int RenderPipeline_BP() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCRN_WIDTH, SCRN_HEIGHT, "Root Engine Render Pipeline", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD.\n");
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void RenderCache_Add(const RenderObj* _obj) {
	renderCache[cacheSize] = *_obj;
	cacheSize++;
}
void RenderCache_AddMesh(const char* _scene, ufbx_load_opts* opts, ufbx_error* fbx_error) {
	auto scene = ufbx_load_file(_scene, opts, fbx_error);
	if (!scene) {
		fprintf(stderr, "Failed to load: %s\n", fbx_error->description.data);
		exit(1);
	}
	// decipher the fbx object to get verticies and animations
	for (int i = 0; i < scene->nodes.count; i++) {
		auto node = scene->nodes.data[i];
		if (node->is_root) continue;
		// Create a RenderObj
		if (node->mesh) {
			RenderObj _mesh;
			// node->mesh->vertex_position  gets a vec3 for position, we are going to transform it into
			printf("Mesh %s has %d verts\n", node->element.name.data, node->mesh->num_vertices);
			printf("Mesh %s has %d indicies\n", node->element.name.data, node->mesh->num_indices);
			printf(" - First vert position: (%.2F, %.2F, %.2F)\n", node->mesh->vertex_position[0].x, node->mesh->vertex_position[0].y, node->mesh->vertex_position[0].z);
			printf(" - First vert UV Coord: (%.2F, %.2F)\n", node->mesh->vertex_uv[0].x, node->mesh->vertex_uv[0].y);
			
			
		}
	}
}
void RenderCache_Draw(glm::mat4 _view, glm::mat4 _proj, float _time) {
	for (int i = 0;i < cacheSize; i++)
	{
		printf("%.1F\n", rotationSpeed);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(renderCache[i].xPos, renderCache[i].yPos, renderCache[i].zPos));
		model = glm::rotate(model, glm::radians(rotationSpeed), glm::vec3(0.5f, 1.0f, 0.0f));
		renderCache[i].objShader.setMat4("view", _view);
		renderCache[i].objShader.setMat4("projection", _proj);
		renderCache[i].objShader.setMat4("model", model);
		RenderObj_Draw(&renderCache[i]);
	}
}
void RenderCache_Clear() {
	for (int i = 0; i < cacheSize; i++)
	{
		RenderObj_Terminate(&renderCache[i]);
	}
	free(renderCache);
	cacheSize = 0;
}

void processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)	{
		
		
	}

}