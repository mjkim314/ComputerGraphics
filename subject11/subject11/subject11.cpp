﻿#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <shader.h>
void render(GLFWwindow* window);

GLuint triangleVB = 0;
GLuint vertexArrayID = 0;
GLuint program = 0;
GLuint indexID = 0;

int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(800, 600, "202126913", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	program = loadShaders("shader.vert", "shader.frag");
	float v[] = { -0.7, -0.7, 0.0, 0.7, -0.7, 0.0, 0.0, 0.7, 0.0 };
	unsigned int indices[3];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	glGenBuffers(1, &triangleVB);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, v, GL_STATIC_DRAW);
	glGenBuffers(1, &indexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVB);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	while (!glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

void render(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.12, 0.69, 0.13, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glBindVertexArray(vertexArrayID);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
}

