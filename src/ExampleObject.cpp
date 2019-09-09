#include <Includes.h>

#include "ExampleObject.h"
#include "engine/import manager/ImportManager.h"

ExampleObject::ExampleObject(glm::vec3 pos, glm::vec3 s ):PObject(pos, s) {
	std::shared_ptr<Model> model = ImportManager::getResourceManager().load<Model>("src\\resources\\models\\nanosuit\\nanosuit.obj");
	std::shared_ptr<Texture2D> texture = ImportManager::getResourceManager().load<Texture2D>("src\\resources\\textures\\container.jpg");
	MaterialConfig materialConfig;
	materialConfig.add<std::shared_ptr<Texture2D>>("textureDiffuse", texture);
	materialConfig.add<std::shared_ptr<Texture2D>>("textureSpecular", texture);
	materialConfig.add<glm::vec3>("diffuseColor", { 0.0f, 0.0f, 1.0f });
	materialConfig.add<float>("shininess", 96.0f);
	materialConfig.add<float>("shininessStrength", 1.0f);

	auto shader = ImportManager::getResourceManager().load<Shader>("src\\resources\\shaders\\basic\\basic.shad");
	std::shared_ptr<Material> material = std::make_shared<Material>(shader);

	//model->setMaterialConfig(0, materialConfig);
	addComponent(COMPONENT_TYPE::MODEL, model);
	addComponent(COMPONENT_TYPE::MATERIAL, material);
}

ExampleObject::~ExampleObject() {

}

void ExampleObject::onUpdate() {
	counter += 0.1f;
	translate({ sin(counter) * 0.01f, 0.0f, 0.0f });
}

void ExampleObject::onEvent(Event &e) {

}