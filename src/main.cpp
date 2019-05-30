#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/import manager/ImportManager.h"
#include "engine/graphics/camera/Camera.h"
#include "engine/objects/PObject.h"

#include <iostream>

ImportManager resourceManager;

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

Camera camera({ 0.0f, 0.0f, -3.0f });

int main()
{
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
	std::shared_ptr<Model> testModel = resourceManager.load<Model>(modelPath);

	std::shared_ptr<Model> testModel2 = resourceManager.load<Model>(modelPath);

	std::shared_ptr<Shader> ourShader = resourceManager.load<Shader>(shaderfile);

	Path container("src\\resources\\textures\\container.jpg");
	std::shared_ptr<Texture2D> texture = resourceManager.load<Texture2D>(container);

	std::shared_ptr<Material> testMaterial(new Material());
	testMaterial->addTexture2D("texture_diffuse0",texture);

	PObject testObject;
	testObject.addComponent(COMPONENT_TYPE::MATERIAL, testMaterial);
	testObject.addComponent(COMPONENT_TYPE::MODEL, testModel);

	testModel2->setMaterial(0, *testMaterial); // fix this
	PObject testObject2({25, 0, 0});
	testObject2.addComponent(COMPONENT_TYPE::MATERIAL, testMaterial);
	testObject2.addComponent(COMPONENT_TYPE::MODEL, testModel2);

	// create transformations
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

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

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//testObject.translate({ sin(currentFrame) * 0.2f, 0.0f, 0.0f });

		// render container
		draw(testObject, camera, projection, ourShader);
		draw(testObject2, camera, projection, ourShader);

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
		camera.translate(camera.getFront() * velocity);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.translate(camera.getFront() * -velocity);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.translate(camera.getRight() * -velocity);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.translate(camera.getRight() * velocity);
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
	camera.rotate(mouseX_Sensitivity * mouse_delta.x, { 0, 1, 0 }, SPACE::WORLD);
	camera.rotate(mouseX_Sensitivity * mouse_delta.y, {1, 0, 0}, SPACE::LOCAL);
	
}