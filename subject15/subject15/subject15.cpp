#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
void render(GLFWwindow* window);

GLuint triangleVB = 0;
GLuint vertexArrayID = 0;
GLuint program = 0;
GLuint indexID = 0;
float radian = 0;

int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(800, 600, "202126913", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	program = loadShaders("shader.vert", "shader.frag");
	float v[] = { 0.0, 0.7, 0.0, -0.35, 0.0, 0.0, 0.35, 0.0, 0.0, -0.7, -0.7, 0.0, 0.0, -0.7, 0.0, 0.7, -0.7, 0.0 };
	unsigned int indices[9] = { 0, 1, 2, 1, 3, 4, 2, 4, 5 };
	glGenBuffers(1, &triangleVB);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, v, GL_STATIC_DRAW);
	glGenBuffers(1, &indexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 9, indices, GL_STATIC_DRAW);

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
	mat3 scaleMat(0.5, 0, 0, 0, 0.5, 0, 0, 0, 1);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	radian += 0.05;
	mat3 rotMat(cos(radian), sin(radian), 0, -sin(radian), cos(radian), 0, 0, 0, 1);

	glUseProgram(program);
	GLuint loc = glGetUniformLocation(program, "tf");
	glUniformMatrix3fv(loc, 1, 0, glm::value_ptr(rotMat));
	//glUniformMatrix3fv(loc, 1, 0, glm::value_ptr(scaleMat));
	glBindVertexArray(vertexArrayID);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
}

