#include "Includes.h"

#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Renderer::Renderer(std::shared_ptr<Camera> cam, std::shared_ptr<Shader> shader):activeCam(cam), defaultShader(shader) {

}

Renderer::~Renderer() {
	
}

void Renderer::submitObject(std::shared_ptr<PObject> obj) {
	objects.push_back(obj);
}

void Renderer::submitDirectionalLight(std::shared_ptr<DirectionalLight> dirLight) {
	directionalLights.push_back(dirLight);
}

void Renderer::submitPointLight(std::shared_ptr<PointLight> pointlight) {
	pointLights.push_back(pointlight);
}

void Renderer::submitSpotLight(std::shared_ptr<SpotLight> spotLight) {
	spotLights.push_back(spotLight);
}

void Renderer::draw() {
	defaultShader->use();
	defaultShader->set<glm::mat4>("view", activeCam->getViewMatrix());
	defaultShader->set<glm::mat4>("projection", projectionMatrix);
	defaultShader->set<glm::vec3>("camPos", activeCam->getWorldPosition());

	int count = 0;
	for (auto dirLight : directionalLights) {
		dirLight->use(defaultShader, count);
		count++;
	}

	count = 0;
	for (auto pointLight : pointLights) {
		pointLight->use(defaultShader, count);
		count++;
	}

	count = 0;
	for (auto spotLight : spotLights) {
		spotLight->use(defaultShader, count);
		count++;
	}

	for (auto obj : objects) {
		obj->draw(defaultShader);
	}
}

void Renderer::setDefaultShader(std::shared_ptr<Shader> shader) {
	defaultShader = shader;
}

void Renderer::setActiveCamera(std::shared_ptr<Camera> cam) {
	activeCam = cam;
}

void Renderer::setProjectionMatrix(float FOV, float aspectRatio, float nearPlane, float farPlane) {
	projectionMatrix = glm::perspective(FOV, aspectRatio, nearPlane, farPlane);
}