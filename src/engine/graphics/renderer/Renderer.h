#pragma once

#include "Includes.h"

#include "../../import manager/shader/Shader.h"
#include "../lights/DirectionalLight.h"
#include "../lights/SpotLight.h"
#include "../camera/Camera.h"

class Renderer {
public:
	Renderer(std::shared_ptr<Camera> cam = nullptr, std::shared_ptr<Shader> shader = nullptr);
	~Renderer();

	void submitObject(std::shared_ptr<PObject> obj);
	void submitDirectionalLight(std::shared_ptr<DirectionalLight> dirLight);
	void submitPointLight(std::shared_ptr<PointLight> pointLight);
	void submitSpotLight(std::shared_ptr<SpotLight> spotLight);
	void draw();

	void setDefaultShader(std::shared_ptr<Shader> shader);
	void setActiveCamera(std::shared_ptr<Camera> cam);
	void setProjectionMatrix(float FOV, float aspectRatio, float nearPlane, float farPlane);
private:
	std::vector<std::shared_ptr<PObject>> objects;
	std::vector <std::shared_ptr<DirectionalLight>> directionalLights;
	std::vector <std::shared_ptr<PointLight>> pointLights;
	std::vector <std::shared_ptr<SpotLight>> spotLights;

	std::shared_ptr<Camera> activeCam;
	std::shared_ptr<Shader> defaultShader;
	glm::mat4 projectionMatrix;

};