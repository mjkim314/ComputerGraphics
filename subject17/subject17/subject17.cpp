﻿#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include "j3a.hpp"
void render(GLFWwindow* window);


GLuint triangleVBO = 0;
GLuint vertexArrayID = 0;
GLuint program = 0;
GLuint indexVBOID = 0;

int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(800, 600, "202126913", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	loadJ3A("./bunny.j3a");
	program = loadShaders("shader.vert", "shader.frag");
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	glGenBuffers(1, &triangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glGenBuffers(1, &indexVBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0] * sizeof(glm::u32vec3), triangles[0], GL_STATIC_DRAW);


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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
	glDrawElements(GL_TRIANGLES, nTriangles[0] * 3, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
}

