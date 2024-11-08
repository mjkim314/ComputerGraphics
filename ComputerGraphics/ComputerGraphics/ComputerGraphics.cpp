#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
void render(GLFWwindow* window);
int main(void) {
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(800, 600, "202126913", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
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
	glfwSwapBuffers(window);
}

