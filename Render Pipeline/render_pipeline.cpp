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
		 0.0f,  0.5f,  0.0f,    0.5f,  0.5f, // 0 - top
		-0.5f,  0.0f, -0.5f,    0.0f,  0.0f, // 1 - back left
		 0.5f,  0.0f, -0.5f,    0.0f,  1.0f, // 2 - back right
		-0.5f,  0.0f,  0.5f,    0.0f,  1.0f, // 3 - front left
		 0.5f,  0.0f,  0.5f,    1.0f,  0.0f, // 4 - front right
		 0.0f, -0.5f,  0.0f,    0.5f,  0.5f, // 5 - bottom
		
	};
	unsigned int diamondIndices[] = {
		0, 1, 2,
		0, 2, 4,
		0, 1, 3,
		0, 3, 4,
		5, 2, 1,
		5, 4, 2,
		5, 3, 1,
		5, 4, 3,

	};
	RenderObj diamond;
	diamond.vertCount = sizeof(diamondVerts)/sizeof(float);
	diamond.verticies = (float*)malloc(sizeof(float) * diamond.vertCount);
	for (int i = 0; i < diamond.vertCount; i++) {
		diamond.verticies[i] = diamondVerts[i];
	}
	diamond.vertSize = sizeof(diamondVerts);
	diamond.indicesCount = sizeof(diamondIndices) / sizeof(unsigned int);
	diamond.indicesSize = sizeof(diamondIndices);
	diamond.indices = (unsigned int*)malloc(sizeof(unsigned int) * diamond.indicesCount);
	for (int i = 0; i < diamond.indicesCount; i++) {
		diamond.indices[i] = diamondIndices[i];
	}
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
	RenderObj _mesh;
	unsigned int _totalVerts = 0;
	unsigned int _totalIndices = 0;
	for (int i = 0; i < scene->nodes.count; i++) {
		auto node = scene->nodes.data[i];
		if (node->is_root) continue;
		// Create a RenderObj
		if (node->mesh) {
			_totalVerts += node->mesh->num_vertices * (5);
			_totalIndices += node->mesh->num_indices;		
			
		}
	}
	_mesh.vertCount = _totalVerts;
	_mesh.verticies = (float*)malloc(sizeof(float) * _mesh.vertCount);
	_mesh.vertSize = sizeof(_mesh.verticies)* _mesh.vertCount;
	_mesh.indicesCount = _totalIndices;
	_mesh.indices = (unsigned int*)malloc(sizeof(unsigned int) * _mesh.indicesCount);
	_mesh.indicesSize = sizeof(_mesh.indices)* _mesh.indicesCount;
	int currentVert = 0;
	int currentIndex = 0;
	for (int i = 0; i < scene->nodes.count; i++) {
		auto node = scene->nodes.data[i];
		if (node->is_root) continue;
		// Create a RenderObj
		if (node->mesh) {
			// 
			for (int j = 0;j < node->mesh->num_vertices; j++) {
				// position values
				_mesh.verticies[currentVert] = node->mesh->vertex_position[j].x;
				_mesh.verticies[currentVert + 1] = node->mesh->vertex_position[j].y;
				_mesh.verticies[currentVert + 2] = node->mesh->vertex_position[j].z;
				// texture coords
				_mesh.verticies[currentVert + 3] = node->mesh->vertex_uv[j].x;
				_mesh.verticies[currentVert + 4] = node->mesh->vertex_uv[j].y;
				currentVert += 5;
			}

			int _offset = currentIndex;
			for (int j = 0; j < node->mesh->num_indices; j++) {
				_mesh.indices[currentIndex] = node->mesh->vertex_indices.data[j]+ _offset;
				currentIndex++;
			}
		}
	}
	_mesh.spanCount = 2;
	_mesh.spans = (unsigned int*)malloc((sizeof(unsigned int) * _mesh.spanCount));
	_mesh.spans[0] = 3;
	_mesh.spans[1] = 2;
	_mesh.totalSpan = 5;
	_mesh.objShader = Shader("v_shader.vertshader", "f_shader.fragshader");
	_mesh.textureData = stbi_load("CV22TS.jpg", &_mesh.t_width, &_mesh.t_height, &_mesh.nrChannels, 0);
	_mesh.xPos = 0.0f;
	_mesh.yPos = 0.0f;
	_mesh.zPos = 0.0f;

}
void RenderCache_Draw(glm::mat4 _view, glm::mat4 _proj, float _time) {
	for (int i = 0;i < cacheSize; i++)
	{
		
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

		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			_rotationVec.y = -1.0f;

		}

		// Rotate the render objs up and down
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			_rotationVec.x = -1.0f;

		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			_rotationVec.x = 1.0f;

		}
		Camera_Rotate(mainCamera, _rotationVec, deltaTime);
	}

	
	//_deltaCursorPos = glm::normalize(_deltaCursorPos);
	
	if (glm::length(_deltaCursorPos) > 1) {
		//printf("Current Position: (%.1F, %.1F)\n", _currentCursorPos.x, _currentCursorPos.y);
		//printf("Prev Position: (%.1F, %.1F)\n", cursorPos.x, cursorPos.y);
		//printf("Delta Position: (%.1F, %.1F)\n", _deltaCursorPos.x, _deltaCursorPos.y);
		//_deltaCursorPos = glm::normalize(_deltaCursorPos);
		//Camera_Rotate(mainCamera, glm::vec3(_deltaCursorPos, 1.0), deltaTime);
		//printf("Normalized Delta Position: (%.1F, %.1F)\n", _deltaCursorPos.x, _deltaCursorPos.y);


	}

	// ================================== MOVEMENT ======================================
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || 
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || 
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || 
		glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		glm::vec3 _movementVec = glm::vec3(0.0f);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			_movementVec.x = -1.0f;

		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			_movementVec.x = 1.0f;

		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			_movementVec.z = -1.0f;

		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			_movementVec.z = 1.0f;

		}
		
	}


	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)	{
		
		
	}

}