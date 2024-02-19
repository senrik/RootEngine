#include <stdio.h>
#include <math.h>
#include <vector>
#include "render_object.hpp"
#include "Camera.hpp"
#include <glad/glad.h> //manages function pointers for OpenGL
#include <GLFW/glfw3.h> // Abstraction layer for targeting multiple systems with OpenGL
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
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
void RenderCache_Add(const float* verts, unsigned int _vertCount, unsigned int* indices, unsigned int _indicesCount, const float _xPos, const float _yPos, const float _zPos);
void RenderCache_Draw(glm::mat4, glm::mat4,float);
void RenderCache_Clear();
void RenderCache_AddMesh(const char*, ufbx_load_opts*, ufbx_error*);
#define SCRN_WIDTH 800
#define SCRN_HEIGHT 600
#define RENDER_CACHE_SIZE 200

static RenderObj* renderCache;
static Camera* mainCamera;
glm::highp_dvec2 cursorPos;
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
		 0.0f,  0.5f,  0.0f,    0.5f,  0.5f, // top - 0
		 0.5f,  0.0f,  0.5f,    1.0f,  0.0f, // right - 1
		-0.5f,  0.0f,  0.5f,    0.0f,  0.0f, // left - 2
		 0.5f,  0.0f, -0.5f,    0.0f,  0.0f, // right - 3
		-0.5f,  0.0f, -0.5f,    1.0f,  0.0f, // left - 4
		 0.0f, -0.5f,  0.0f,    0.5f,  0.5f, // bottom - 5
		
	};
	unsigned int diamondindices[] = {
		0, 1, 2,
		5, 1, 2,
		0, 1, 3,
		5, 1, 3,
		0, 3, 4,
		5, 3, 4,
		0, 2, 4,
		5, 2, 4
	};
	RenderCache_Add(diamondVerts, 30, diamondindices, 24, 0, 0, 0);
#pragma endregion
	
	
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
		view = mainCamera->GetViewMatrix();
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

	mainCamera = new Camera();
}

void RenderCache_Add(const float* verts, unsigned int _vertCount, unsigned int* indices, unsigned int _indicesCount, const float _xPos, const float _yPos, const float _zPos) {
	RenderObj obj;
	
	obj.vertCount = _vertCount;
	obj.vertSize = _vertCount * sizeof(float);
	obj.verticies = (float*)malloc(_vertCount * sizeof(float));
	for (int i = 0; i < obj.vertCount; i++) {
		obj.verticies[i] = verts[i];
	}

	//optional for indices
	if (_indicesCount > 0 && indices != NULL) {
		obj.indicesCount = _indicesCount;
		obj.indicesSize = _indicesCount*sizeof(unsigned int);
		obj.indices = (unsigned int*)malloc(sizeof(unsigned int) * obj.indicesCount);
		for (int i = 0; i < obj.indicesCount; i++) {
			obj.indices[i] = indices[i];
		}
	}
	obj.spanCount = 2; // two different attributes to the verticies
	obj.spans = (unsigned int*)malloc((sizeof(unsigned int) * obj.spanCount));
	obj.spans[0] = 3; // position
	obj.spans[1] = 2; // texture coords
	obj.totalSpan = 5;
	obj.objShader = Shader("v_shader.vertshader", "f_shader.fragshader");
	obj.textureData = stbi_load("container.jpg", &obj.t_width, &obj.t_height, &obj.nrChannels, 0);
	obj.xPos = _xPos;
	obj.yPos = _yPos;
	obj.zPos = _zPos;
	//obj.rotation = glm::quat(glm::vec3(0.0f,0.0f,0.0f));

	RenderObj_Init(&obj);
	RenderCache_Add(&obj);
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
			// create the collection of verts
			for (int j = 0; j < node->mesh->num_vertices; j++) {

			}
		}
	}
}
void RenderCache_Draw(glm::mat4 _view, glm::mat4 _proj, float _time) {
	for (int i = 0;i < cacheSize; i++)
	{
		glm::mat4 modelTrans = glm::mat4(1.0f);
		glm::mat4 modelRot = glm::mat4_cast(renderCache[i].rotation);
		
		
		modelTrans = glm::translate(modelTrans, glm::vec3(renderCache[i].xPos, renderCache[i].yPos, renderCache[i].zPos));
		
		renderCache[i].objShader.setMat4("view", _view);
		renderCache[i].objShader.setMat4("projection", _proj);
		renderCache[i].objShader.setMat4("modelTrans", modelTrans);
		renderCache[i].objShader.setMat4("modelRot", modelRot);
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
	glm::highp_dvec2 _currentCursorPos;
	glfwGetCursorPos(window, &_currentCursorPos.x, &_currentCursorPos.y);
	glm::highp_dvec2 _deltaCursorPos = _currentCursorPos - cursorPos;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	// ================================== ROTATION ======================================
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

		
		glm::vec3 _rotationVec = glm::vec3(0.0f);
		// Rotate the render objs to the LEFT AND RIGHT
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			_rotationVec.y = 1.0f;

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


	cursorPos = _currentCursorPos;
}