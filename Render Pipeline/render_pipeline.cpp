#include <stdio.h>
#include <math.h>
#include <vector>
#include <glad/glad.h> //manages function pointers for OpenGL
#include <GLFW/glfw3.h> // Abstraction layer for targeting multiple systems with OpenGL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

#include <stb_image.h> // image loader


#pragma region Callback functions Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#pragma endregion

void processInput(GLFWwindow* window, float deltaTime);

// Render Pipeline boiler plate code
int RenderPipeline_BP();

// adds a renderable object to the queue to be draw.
void RenderPipeline_Queue();




#define SCRN_WIDTH 800
#define SCRN_HEIGHT 600

static GLFWwindow* window;

int main(int argc, char* argv[]) {
  

#pragma region Boiler Plate
	RenderPipeline_BP();
#pragma endregion

#pragma region Vert and Indicies
	//float vertices[] = {
 //       // positions         // texture coords
 //       0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // front top right
	//	  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // front bottom left
	//   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // front bottom left
	//   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // front top left
	//    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	//	  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	//   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	//   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 //   };
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float diamondVerts[] = {
		 // position			// texcoords
		 0.0f,  0.5f,  0.0f,    0.0f,  1.0f,
		-0.5f,  0.0f,  0.0f,    1.0f, -1.0f,
		 0.0f,  0.0f, -0.5f,   -1.0f,  1.0f,

		 0.0f, -0.5f,  0.0f,    0.0f, -1.0f,
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

	unsigned int indicies[] = {
		0,1,3, // first triangle (f)
		1,2,3, // second triangle (f)
		4,5,0, // third triangle (r)
		5,1,0, // fourth triangle (r)
		7,6,4, // fifth triangle (b)
		6,5,4, // sixth triangle (b)
		3,2,7, // seventh triangle (l)
		2,6,7  // eigth triangle (l)
	};

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};
#pragma endregion

#pragma region Shader Program Creation
	//Shader ourShader("shader.vs", "shader.fs");
	Shader ourShader("shader.vertshader","shader.fragshader");
#pragma endregion

	// buffer objects - created outside of individual objects, or does each object have its own buffer objects?
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // generating one buffer, using VBO's address as the id
	glGenBuffers(1, &EBO); // generating one buffer, using EBO's address as the id

	glBindVertexArray(VAO);

	// vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // binding the GL_ARRAY_BUFFER to VBO, action affecting the GL_ARRAY_BUFFER will affect VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// vertex position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds VBO since it is now being tracked via the glVertexAttribPointer call

#pragma region Texture
	// texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// wrapping params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Texture filter settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// border color
	/*float borderColor[] = { 1.0f,1.0f,0.0f,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);*/

	// load image data
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	// Generate mipmaps
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Gailed to load texture.\n");
	}
	stbi_image_free(data);
#pragma endregion


	//glBindVertexArray(0);
	// rainbow vertex color shader
	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);
	float deltaTime = 0;
	while (!glfwWindowShouldClose(window)) {
		float timeValue = glfwGetTime();
		deltaTime = timeValue - deltaTime;
		// INPUT
		processInput(window, deltaTime);


		// RENDER CALLS
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		// activate shader
		ourShader.use();


		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// set the camera space
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		// set the perspective matrix
		proj = glm::perspective(glm::radians(45.0f), (float)SCRN_WIDTH / (float)SCRN_HEIGHT, 0.01f, 1000.0f);
		
		// get the "view" uniform and set it to the view matrix
		ourShader.setMat4("view", view);
		// get the "perspective" uniform and set it to the projection matrix
		ourShader.setMat4("projection", proj);

		//model = glm::rotate(model, glm::radians(50.0f) * deltaTime, glm::vec3(0.5f, 1.0f, 0.0f));

		// Draw the stuff
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++) {
			
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle= 30.0f * i;
			model = glm::rotate(model, glm::radians(angle) *timeValue, glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		// Update delta time
		deltaTime = timeValue;
	}

	// clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	ourShader.terminateShader();
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

void processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}