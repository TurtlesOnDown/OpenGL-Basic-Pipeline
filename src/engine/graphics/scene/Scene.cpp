#include <Includes.h>

#include "Scene.h"

void Scene::push(std::string name, std::shared_ptr<PObject> obj) {
	if (objects.find(name) != objects.end()) {
		LOG_WARN("SCENE::OBJECT WITH NAME ALREADY EXISTS");
		return;
	}
	objects[name] = obj;
}

void Scene::onUpdate() {
	for (auto object : objects) {
		// Add onUpdate function to objects
		object.second->onUpdate();
	}
}

void Scene::onEvent(Event &event) {
	for (auto object : objects) {
		// Add onEvent function to objects
		object.second->onEvent(event);
	}
}