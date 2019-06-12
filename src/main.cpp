#include "Includes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/import manager/ImportManager.h"
#include "engine/graphics/renderer/Renderer.h"

#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

ImportManager resourceManager;
Renderer openGLRenderer;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec2 mousePosition(SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f);

bool firstMouse = true;

std::shared_ptr<Camera> camera(new Camera({ 0.0f, 0.0f, -3.0f }));

#include "engine/common/Log.h"

int main()
{
	Log::init();

	LOG_ERROR("Hello world.");
	LOG_TRACE("Hello world.");
	LOG_INFO("Hello world.");
	LOG_WARN("Hello world.");
	LOG_CRITICAL("Hello world.");

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	Path shaderfile("src\\resources\\shaders\\basic\\basic.shad");

	Path modelPath("src\\resources\\models\\nanosuit\\nanosuit.obj");
	Path containerPath("src\\resources\\models\\testCube\\test.obj");
	//Path untiltedPath("src\\resources\\models\\untitled\\untitled.obj");
	std::shared_ptr<Model> testModel = resourceManager.load<Model>(modelPath);
	std::shared_ptr<Model> testCube = resourceManager.load<Model>(containerPath);
	//std::shared_ptr<Model> testUntitled = resourceManager.load<Model>(untiltedPath);

	//std::shared_ptr<Model> testModel2 = resourceManager.load<Model>(modelPath);

	std::shared_ptr<Shader> ourShader = resourceManager.load<Shader>(shaderfile);

	Path container("src\\resources\\textures\\container.jpg");
	std::shared_ptr<Texture2D> texture = resourceManager.load<Texture2D>(container);

	std::shared_ptr<Material> testMaterial(new Material());
	testMaterial->addTexture2D("texture_diffuse0",texture);

	testCube->setMaterial(0, *testMaterial);

	std::shared_ptr<PObject> testObject(new PObject());
	testObject->addComponent(COMPONENT_TYPE::MATERIAL, testMaterial);
	testObject->addComponent(COMPONENT_TYPE::MODEL, testCube);

	std::shared_ptr<PObject> testObject3(new PObject({3, 0, 0}));
	testObject3->addComponent(COMPONENT_TYPE::MATERIAL, testMaterial);
	testObject3->addComponent(COMPONENT_TYPE::MODEL, testCube);

	std::shared_ptr<PObject> testObject4(new PObject({0, 3, 0}));
	testObject4->addComponent(COMPONENT_TYPE::MATERIAL, testMaterial);
	testObject4->addComponent(COMPONENT_TYPE::MODEL, testCube);

	std::shared_ptr<PObject> testObject2(new PObject({ 0, 0, 0 }));
	testObject2->addComponent(COMPONENT_TYPE::MATERIAL, testMaterial);
	testObject2->addComponent(COMPONENT_TYPE::MODEL, testModel);

	std::shared_ptr<DirectionalLight> sunLight(new DirectionalLight({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }));

	openGLRenderer.setActiveCamera(camera);
	openGLRenderer.setDefaultShader(ourShader);
	//openGLRenderer.submitObject(testObject);
	openGLRenderer.submitObject(testObject2);
	//openGLRenderer.submitObject(testObject3);
	//openGLRenderer.submitObject(testObject4);
	openGLRenderer.submitDirectionalLight(sunLight);
	//openGLRenderer.submitObject(testObject2);
	// create transformations
	//glm::mat4 projection = glm::mat4(1.0f);
	openGLRenderer.setProjectionMatrix(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//testObject->rotate(glm::radians(45.0f), { 1, 1, 0 }, SPACE::LOCAL);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);
		sunLight->translate({ cos(currentFrame) * 0.01f, 0.0f, 0.0f});
		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		testObject->rotate(sin(currentFrame) * 0.02f, { 1, 1, 0 }, SPACE::LOCAL);

		// render container
		openGLRenderer.draw();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float velocity = 10.0f * deltaTime;

	

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->translate(camera->getFront() * velocity);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->translate(camera->getFront() * -velocity);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->translate(camera->getRight() * -velocity);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->translate(camera->getRight() * velocity);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		mousePosition = { xpos, ypos };
		firstMouse = false;
	}

	glm::vec2 mouse_delta = glm::vec2(xpos, ypos) - mousePosition;

	//notice that we reduce the sensitvity
	const float mouseX_Sensitivity = 0.002f;
	const float mouseY_Sensitivity = 0.002f;

	mousePosition = { xpos, ypos };
	camera->rotate(mouseX_Sensitivity * mouse_delta.x, { 0, 1, 0 }, SPACE::WORLD);
	camera->rotate(mouseX_Sensitivity * mouse_delta.y, {1, 0, 0}, SPACE::LOCAL);
	
}