#include <Includes.h>

#include "ExampleObject.h"
#include "engine/import manager/ImportManager.h"

ExampleObject::ExampleObject(glm::vec3 pos, glm::vec3 s ):PObject(pos, s) {
	std::shared_ptr<Model> model = ImportManager::getResourceManager().load<Model>("src\\resources\\models\\cube\\cube.obj");
	std::shared_ptr<Texture2D> texture = ImportManager::getResourceManager().load<Texture2D>("src\\resources\\textures\\container.jpg");
	std::shared_ptr<Material> material(new Material());
	material->add<std::shared_ptr<Texture2D>>("textureDiffuse", texture);
	material->add<std::shared_ptr<Texture2D>>("textureSpecular", texture);
	material->add<glm::vec3>("diffuseColor", { 0.0f, 0.0f, 1.0f });
	material->add<float>("shininess", 96.0f);
	material->add<float>("shininessStrength", 1.0f);

	model->setMaterial(0, *material);
	addComponent(COMPONENT_TYPE::MODEL, model);
}

ExampleObject::~ExampleObject() {

}

void ExampleObject::onUpdate() {
	counter += 0.1f;
	translate({ sin(counter) * 0.01f, 0.0f, 0.0f });
}

void ExampleObject::onEvent(Event &e) {

}