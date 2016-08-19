#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

const int width == 600, height == 600;

int main(int argc, char *argv[]) {
	if( glfwInit() == GL_FALSE) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow *window = glfwCreateWindow(width, height, "Learn OpenGL", NULL, NULL);
	if(window == NULL) {
		fprintf(stderr, "Failed to create window\n");
		glfwTermiante();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if(glewInit != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		exit(-1);
	}
	
	glViewport(width, height, 0, 0);
	while(glfwWindowShouldClose(window) != GL_TRUE) {
		glfwPollEvents();
	}
	
	return 0;
}
