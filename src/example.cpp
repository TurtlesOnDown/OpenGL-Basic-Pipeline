#include <Includes.h>

#include "engine/core/Application.h"
#include "engine/graphics/camera/Camera.h"
#include "engine/graphics/scene/Scene.h"
#include "ExampleObject.h"

class ExampleLayer : public Layer {
public:
	ExampleLayer() {
		scene.push("TestCube", std::make_shared<ExampleObject>());
		scene.push("TestCube1", std::make_shared<ExampleObject>()); // TODO: Fix the double update created by adding a child of an object to a scene
		scene.push("TestCube2", std::make_shared<ExampleObject>(glm::vec3{0.0f, 3.0f, 0.0f}));

		scene.get("TestCube")->addChild(scene.get("TestCube"), scene.get("TestCube1")); 
		scene.get("TestCube1")->translate({ 3, 0, 0 });

		OpenGLAPI::enable(GL_DEPTH_TEST);

		int width = Application::Get().GetWindow().getWidth();
		int height = Application::Get().GetWindow().getHeight();
		camera = std::make_shared<Camera>(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f), PERSPECTIVE_CONFIG::PROJECTION, glm::vec3(0.0f, 0.0f, 3.0f));
		shader = ImportManager::getResourceManager().load<Shader>("src\\resources\\shaders\\basic\\basic.shad");
		sunLight = std::make_shared<DirectionalLight>(glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.0f, 10.0f, 10.0f });

		std::shared_ptr<Material> testMarterial = std::make_shared<Material>(shader); // TODO: Remove this later

		auto &renderer = Renderer::getRenderer();

		renderer.setActiveCamera(camera); // TODO: fix this by unknown solution
		renderer.setDefaultShader(shader); // TODO: Fix this by making the shader part of the material

		renderer.submitDirectionalLight(sunLight);

		for (auto object : scene) {
			renderer.submitObject(object.second);
		}
	}

	void onUpdate() override {
		for (auto object : scene) {
			object.second->onUpdateChildren();
		}

		OpenGLAPI::clearColor(0.2f, 0.2f, 0.2f, 1.0f);
		OpenGLAPI::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Renderer::getRenderer().draw();
	}

private:
	Scene scene;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<DirectionalLight> sunLight;
};

class ExampleApp : public Application {
public:
	ExampleApp() {
		pushLayer(std::make_unique<ExampleLayer>());
	}

	~ExampleApp() {
		
	}
};

Application *CreateApplication() {
	return new ExampleApp();
}