#include "Includes.h"

#include "Object.h"
#include <glm/gtc/quaternion.hpp>

#include "../import manager/shader/Shader.h"
#include "Component.h"

#ifndef POBJECTCLASS
#define POBJECTCLASS

// Placeable object that have a location, direction, and a size. Can have attached components

class Camera; // TODO remove when fixing draw function

enum class SPACE {WORLD, LOCAL};

class PObject : public Object {
public:
	PObject(glm::vec3 pos = { 0.0f, 0.0f, 0.0f }, glm::vec3 s = {1.0f, 1.0f, 1.0f});
	virtual ~PObject() override;

	virtual void onUpdate() override;
	virtual void onEvent(Event &e) override;
	void onUpdateChildren();

	void translate(glm::vec3 trans);
	void scaleAdd(glm::vec3 s);
	void scaleMult(glm::vec3 s);
	void rotate(float angle, glm::vec3 axis, SPACE relativeTo); // Angle in radians, axis to rotate around, and relative space

	glm::vec3 getWorldPosition() const;
	glm::quat getWorldOrienation() const;
	
	glm::vec3 getWorldFront() const;
	glm::vec3 getWorldRight() const;
	glm::vec3 getWorldUp() const;
	glm::mat4 getModelMatrix();

	
	glm::vec3 getLocalPosition() const { return localPosition; }
	glm::vec3 getLocalScale() const { return localScale; }
	glm::quat getLocalOrientation() const { return localOrientation; }

	glm::vec3 getLocalFront() const { return glm::vec3(0.0f, 0.0f, -1.0f) * localOrientation; }
	glm::vec3 getLocalRight() const { return glm::vec3(1.0f, 0.0f, 0.0f) * localOrientation; }
	glm::vec3 getLocalUp() const { return glm::vec3(0.0f, 1.0f, 0.0f) * localOrientation; }
	std::shared_ptr<PObject> getParent() const { return parent.lock(); }

	static void addChild(std::shared_ptr<PObject> parent, std::shared_ptr<PObject> child);
	inline void addComponent(COMPONENT_TYPE type, std::shared_ptr<Component> comp) { components[type] = comp; }

	void draw(const std::shared_ptr<Shader> shader);

protected:
	glm::vec3 localPosition;
	glm::vec3 localScale;
	glm::quat localOrientation;

	std::weak_ptr<PObject> parent;
	std::vector<std::shared_ptr<PObject>> children;

	std::map<COMPONENT_TYPE, std::shared_ptr<Component>> components;

	friend struct Transform;
};

#endif // !POBJECTCLASS

