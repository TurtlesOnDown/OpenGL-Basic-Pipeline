#pragma once

#include <map>
#include "../../objects/PObject.h"
#include "../../core/events/Event.h"

class Scene {
public:
	Scene() {};
	~Scene() {};

	void push(std::string name, std::shared_ptr<PObject> obj);
	std::shared_ptr<PObject> get(std::string name) { return objects[name]; }
	void remove(std::string name) { objects.erase(name); }

	void onUpdate();
	void onEvent(Event &event);

	std::map<std::string, std::shared_ptr<PObject>>::iterator begin() { return objects.begin(); }
	std::map<std::string, std::shared_ptr<PObject>>::iterator end() { return objects.end(); }
private:
	std::map<std::string, std::shared_ptr<PObject>> objects;
};