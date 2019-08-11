#include "Includes.h"

#include "GLFWWindow.h"

static bool GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char *description) {
	LOG_ERROR("GLFW::Error::{0}::{1}", error, description);
}

Window *Window::Create(const WindowConfigs &c) {
	return new GLFWWindowClass(c);
}

GLFWWindowClass::GLFWWindowClass(const WindowConfigs &c) {
	Init(c);
}

GLFWWindowClass::~GLFWWindowClass() {
	Destroy();
}

void GLFWWindowClass::Init(const WindowConfigs &c) {
	config.name = c.name;
	config.width = c.width;
	config.height = c.height;

	if (!GLFWInitialized) {
		int success = glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);
		GLFWInitialized = true;
	}

	window = glfwCreateWindow((int)config.width, (int)config.height, config.name.c_str(), nullptr, nullptr);

	// TODO: OpenGL context creation

	glfwSetWindowUserPointer(window, &config);

	// TODO: Event call back functions
}

void GLFWWindowClass::Destroy() {
	glfwDestroyWindow(window);
}