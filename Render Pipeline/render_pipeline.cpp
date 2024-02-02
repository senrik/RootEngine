#include <stdio.h>
#include <math.h>
#include <glad/glad.h> //manages function pointers for OpenGL
#include <GLFW/glfw3.h> // Abstraction layer for targeting multiple systems with OpenGL
#include "shader.hpp"
#include <stb_image.h> // image loader


#pragma region Callback functions Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#pragma endregion

void processInput(GLFWwindow* window, float deltaTime);

int main(int argc, char* argv[]) {

#pragma region Boiler Plate
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGl", NULL, NULL);
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

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#pragma endregion

	float vertices[] = {
        // positions        // colors          // texture coords
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f

    };
	unsigned int indicies[] = {
		0,1,3,
		1,2,3
	};
	float texCoords[] = {
		0.0f,0.0f,
		1.0f, 0.0f,
		0.5f,1.0f
	};

#pragma region Shader Program Creation
	Shader ourShader("shader.vs", "shader.fs");
#pragma endregion

	unsigned int VAO, VBO, EBO, texture;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // generating one buffer, using VBO's address as the id
	glGenBuffers(1, &EBO); // generating one buffer, using VBO's address as the id
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // binding the GL_ARRAY_BUFFER to VBO, action affecting the GL_ARRAY_BUFFER will affect VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute [attrib index], [number of values], [value type], [normalize data flag], [stride], [offset to first attribute in array]
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds VBO since it is now being tracked via the glVertexAttribPointer call

#pragma region Texture

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// clamping image Mipmap & Texture filter settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// border color
	/*float borderColor[] = { 1.0f,1.0f,0.0f,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);*/

	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
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
		glClear(GL_COLOR_BUFFER_BIT);

		//ourShader.setFloat("xOffset", sin(timeValue) / 10.0f);
		//ourShader.setFloat("yOffset", cos(timeValue) / 10.0f);

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		



		glfwSwapBuffers(window);
		glfwPollEvents();

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

void processInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}