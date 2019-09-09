#include "Includes.h"

#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../import manager/material/Material.h"

std::unique_ptr<Renderer> Renderer::renderer = std::make_unique<Renderer>();

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
		// TODO: make this based on material not on object

	for (auto obj : objects) {
		auto material = std::dynamic_pointer_cast<Material>(obj->getComponent(COMPONENT_TYPE::MATERIAL));
		auto &shader = material->getShader();
		shader->use();
		shader->set<glm::mat4>("view", activeCam->getViewMatrix());
		shader->set<glm::mat4>("projection", activeCam->getPerspectiveMatrix());
		shader->set<glm::vec3>("camPos", activeCam->getWorldPosition());

		int count = 0;
		for (auto dirLight : directionalLights) {
			dirLight->use(shader, count);
			count++;
		}

		count = 0;
		for (auto pointLight : pointLights) {
			pointLight->use(shader, count);
			count++;
		}

		count = 0;
		for (auto spotLight : spotLights) {
			spotLight->use(shader, count);
			count++;
		}

		obj->draw(material);
	}
}

void Renderer::setDefaultShader(std::shared_ptr<Shader> shader) {
	defaultShader = shader;
}

void Renderer::setActiveCamera(std::shared_ptr<Camera> cam) {
	activeCam = cam;
}