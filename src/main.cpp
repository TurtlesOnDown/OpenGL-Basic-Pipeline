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
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec2 mousePosition(SCR_WIDTH / 2.0f, SCR_HEIGHT / 2.0f);

bool firstMouse = true;

std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3( 0.0f, 0.0f, 3.0f ));

std::shared_ptr<SpotLight> flashLight(new SpotLight({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }));

int main()
{
	Log::init();

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
		LOG_ERROR("Failed to create GLFW window");
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
		LOG_ERROR("Failed to initialize GLAD");
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);


	//Path untiltedPath("src\\resources\\models\\untitled\\untitled.obj");
	//std::shared_ptr<Model> testModel = resourceManager.load<Model>("src\\resources\\models\\nanosuit\\nanosuit.obj");
	std::shared_ptr<Model> testCube = resourceManager.load<Model>("src\\resources\\models\\cube\\cube.obj");
	std::shared_ptr<Model> testCube1 = resourceManager.load<Model>("src\\resources\\models\\cube\\cube.obj");
	std::shared_ptr<Model> testCube2 = resourceManager.load<Model>("src\\resources\\models\\cube\\cube.obj");
	//std::shared_ptr<Model> testUntitled = resourceManager.load<Model>("src\\resources\\models\\untitled\\untitled.obj");

	//std::shared_ptr<Model> testModel2 = resourceManager.load<Model>(modelPath);

	std::shared_ptr<Shader> ourShader = resourceManager.load<Shader>("src\\resources\\shaders\\basic\\basic.shad");

	std::shared_ptr<Texture2D> texture = resourceManager.load<Texture2D>("src\\resources\\textures\\container.jpg");

	std::shared_ptr<Material> testMaterial(new Material());
	testMaterial->add<std::shared_ptr<Texture2D>>("textureDiffuse",texture);
	testMaterial->add<std::shared_ptr<Texture2D>>("textureSpecular", texture);
	testMaterial->add<glm::vec3>("diffuseColor", { 0.0f, 0.0f, 1.0f });
	testMaterial->add<float>("shininess", 96.0f);
	testMaterial->add<float>("shininessStrength", 1.0f);

	std::shared_ptr<Material> testMaterial1(new Material());
	testMaterial1->add<std::shared_ptr<Texture2D>>("textureDiffuse", texture);
	testMaterial1->add<glm::vec3>("diffuseColor", { 1.0f, 0.0f, 0.0f });

	std::shared_ptr<Material> testMaterial2(new Material());
	testMaterial2->add<std::shared_ptr<Texture2D>>("textureDiffuse", texture);
	testMaterial2->add<glm::vec3>("diffuseColor", { 0.0f, 1.0f, 0.0f });

	testCube->setMaterial(0, *testMaterial);
	testCube1->setMaterial(0, *testMaterial1);
	testCube2->setMaterial(0, *testMaterial2);

	std::shared_ptr<PObject> testObject(new PObject());
	testObject->addComponent(COMPONENT_TYPE::MODEL, testCube);

	std::shared_ptr<PObject> testObject3(new PObject({3, 0, 0}));
	testObject3->addComponent(COMPONENT_TYPE::MODEL, testCube1);
	PObject::addChild(testObject, testObject3);

	std::shared_ptr<PObject> testObject4(new PObject({0, 3, 0}));
	testObject4->addComponent(COMPONENT_TYPE::MODEL, testCube2);
	PObject::addChild(testObject3, testObject4);

	std::shared_ptr<PObject> testObject2(new PObject({ 0, 0, 0 }));
	//testObject2->addComponent(COMPONENT_TYPE::MODEL, testModel);

	std::shared_ptr<PObject> copyModel1(new PObject({ 0, 0, 3.0f }));
	//copyModel1->addComponent(COMPONENT_TYPE::MODEL, testModel);

	std::shared_ptr<PObject> copyModel2(new PObject({ 0, 0, -3.0f }));
	//copyModel2->addComponent(COMPONENT_TYPE::MODEL, testModel);

	std::shared_ptr<DirectionalLight> sunLight(new DirectionalLight({ 1.0f, 1.0f, 1.0f }, { 0.0f, 10.0f, 10.0f }));
	std::shared_ptr<PointLight> cameraLight(new PointLight({ 1.0f, 1.0f, 1.0f }, { 0.0f, 3.0f, 3.0f }));
	
	//PObject::addChild(camera, flashLight);

	openGLRenderer.setActiveCamera(camera);
	openGLRenderer.setDefaultShader(ourShader);
	openGLRenderer.submitObject(testObject);
	//openGLRenderer.submitObject(testObject2);
	openGLRenderer.submitObject(testObject3);
	openGLRenderer.submitObject(testObject4);
	//openGLRenderer.submitObject(copyModel2);
	//openGLRenderer.submitObject(copyModel1);
	openGLRenderer.submitDirectionalLight(sunLight);
	//openGLRenderer.submitPointLight(cameraLight);
	//openGLRenderer.submitSpotLight(flashLight);
	//openGLRenderer.submitObject(testObject2);
	// create transformations
	//glm::mat4 projection = glm::mat4(1.0f);
	openGLRenderer.setProjectionMatrix(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//testObject->rotate(glm::radians(45.0f), { 1, 1, 0 }, SPACE::LOCAL);
	//flashLight->rotate(glm::radians(22.5f), { 0, 1, 0 }, SPACE::WORLD);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		float fps = 1.0 / deltaTime;
		glfwSetWindowTitle(window, std::to_string(fps).c_str());

		// input
		// -----
		processInput(window);
		//sunLight->translate({ cos(currentFrame) * 0.05f, 0.0f, 0.0f});
		//cameraLight->setPosition(camera->getPosition());
		//flashLight->setPosition(camera->getPosition());
		testObject->translate({sin(currentFrame) * 0.05f, 0.0f, 0.0f});
		testObject3->translate({ 0.0f, sin(currentFrame) * 0.05f, 0.0f });
		testObject4->translate({ 0.0f, 0.0f, sin(currentFrame) * 0.05f });
		//testObject->rotate(currentFrame *0.002f, { 0, 0, 1 }, SPACE::WORLD);
		//testObject3->rotate(currentFrame *0.002f, { 1, 0, 0 }, SPACE::WORLD);
		//testObject4->rotate(currentFrame * 0.002f, { 0, 1, 0 }, SPACE::WORLD);
		//testObject4->scaleAdd({ sin(currentFrame) * 0.05f, sin(currentFrame) * 0.05f, sin(currentFrame) * 0.05f });

		// render
		// ------
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//testObject->rotate(sin(currentFrame) * 0.02f, { 1, 1, 0 }, SPACE::LOCAL);

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
		camera->translate(camera->getWorldFront() * velocity);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->translate(camera->getWorldFront() * -velocity);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->translate(camera->getWorldRight() * -velocity);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->translate(camera->getWorldRight() * velocity);
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

	//flashLight->rotate(mouseX_Sensitivity * mouse_delta.x, { 0, 1, 0 }, SPACE::WORLD);
	//flashLight->rotate(mouseX_Sensitivity * mouse_delta.y, { 1, 0, 0 }, SPACE::LOCAL);
	
}