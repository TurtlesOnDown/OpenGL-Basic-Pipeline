#include "Includes.h"

#include "GLFWWindow.h"

#include "../../core/events/ApplicationEvent.h"
#include "../../core/events/MouseEvent.h"
#include "../../core/events/KeyEvent.h"

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
	data.name = c.name;
	data.width = c.width;
	data.height = c.height;

	if (!GLFWInitialized) {
		int success = glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);
		GLFWInitialized = true;
	}

	window = glfwCreateWindow((int)data.width, (int)data.height, data.name.c_str(), nullptr, nullptr);

	// TODO: plaform independant context creation
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG_ERROR("Failed to initialize GLAD");
		assert(false); // TODO: make this cleaner
	}
	
	glfwSetWindowUserPointer(window, &data);

	// Callbacks
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		GLFWWindowData &data = *(GLFWWindowData *)glfwGetWindowUserPointer(window);
		data.width = width;
		data.height = height;

		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	});

	glfwSetWindowCloseCallback(window, [](GLFWwindow * window) {
		GLFWWindowData &data = *(GLFWWindowData *)glfwGetWindowUserPointer(window);

		WindowCloseEvent event;
		data.EventCallback(event);
	});

	glfwSetKeyCallback(window, [](GLFWwindow * window, int key, int scancode, int action, int mods) {
			GLFWWindowData &data = *(GLFWWindowData *)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
	});

	glfwSetCharCallback(window, [](GLFWwindow * window, unsigned int keycode) {
			GLFWWindowData &data = *(GLFWWindowData *)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow * window, int button, int action, int mods) {
			GLFWWindowData &data = *(GLFWWindowData *)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
	});

	glfwSetScrollCallback(window, [](GLFWwindow * window, double xOffset, double yOffset) {
			GLFWWindowData &data = *(GLFWWindowData *)glfwGetWindowUserPointer(window);

			MouseScrollEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow * window, double xPos, double yPos) {
			GLFWWindowData &data = *(GLFWWindowData *)glfwGetWindowUserPointer(window);

			MouseMoveEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
	});
}

void GLFWWindowClass::Destroy() {
	glfwDestroyWindow(window);
}

void GLFWWindowClass::onUpdate() {
	glfwPollEvents();
	glfwSwapBuffers(window); // TODO: make platform independant
}