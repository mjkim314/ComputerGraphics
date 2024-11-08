#define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include "j3a.hpp"
void render(GLFWwindow* window);


GLuint triangleVBO = 0;
GLuint vertexArrayID = 0;
GLuint program = 0;
GLuint indexVBOID = 0;
float camDist = 4;
float phi = 4.0;
float theta = 45.0;
float fov = 1.04719755;
double lastX = 500;
double lastY = 500;

void mouseButtonCB(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &lastX, &lastY);
	}
}

void cursorPosCB(GLFWwindow* window, double xpos, double ypos) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
		theta -= (xpos - lastX) / width * 3.141592;
		phi -= (ypos - lastY) / height * 3.141592;
		lastX = xpos;
		lastY = ypos;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	fov -= yoffset * 0.005;
	if (fov > M_PI - 0.01) {
		fov = M_PI - 0.01;
	}
	if (fov < 0.01) {
		fov = 0.01;
	}
}

int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(800, 600, "202126913", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetMouseButtonCallback(window, mouseButtonCB);
	glfwSetCursorPosCallback(window, cursorPosCB);
	glfwSetScrollCallback(window, scroll_callback);

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

	glm::vec3 beforeRo = glm::vec3(0.0, 0.0, camDist);
	glm::vec4 RoCar = glm::vec4(beforeRo, 0.0);
	glm::mat4 roMatY = glm::rotate(theta, glm::vec3(0, 1, 0));
	glm::mat4 roMatX = glm::rotate(phi, glm::vec3(1, 0, 0));
	RoCar = RoCar * roMatY * roMatX;
	glm::vec3 cameraPos = glm::vec3(RoCar.x, RoCar.y, RoCar.z);
	glm::mat4 viewMat = glm::lookAt(cameraPos, glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 ProjMat = glm::perspective(fov, width / (float)height, 0.01f, 100.0f);//float으로 통일, Near, Far를 float으로 명시

	glUseProgram(program);
	GLuint loc = glGetUniformLocation(program, "viewMat");
	glUniformMatrix4fv(loc, 1, 0, glm::value_ptr(viewMat));
	GLuint loc2 = glGetUniformLocation(program, "projMat");
	glUniformMatrix4fv(loc2, 1, 0, glm::value_ptr(ProjMat));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
	glDrawElements(GL_TRIANGLES, nTriangles[0] * 3, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
}

