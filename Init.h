#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* Window;
int width, height;

GLFWwindow* initialize() {

	//initialize glfw
	if (glfwInit() != GLFW_TRUE) {
		fprintf(stderr, "Failed to initialized! \n");
		return NULL;
	}

	width = 1366;
	height = 768;

	// set opengl version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window 
	GLFWwindow* window;
	window = glfwCreateWindow(width, height, "Apolinar & Santonia", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to load window! \n");
		return NULL;
	}
	glfwMakeContextCurrent(window);

	//initialize glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return NULL;
	}

	return Window;
}


int getWidth() {
	return width;
}

int getHeight() {
	return height;
}