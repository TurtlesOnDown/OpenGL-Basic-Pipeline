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

class PObject : protected Object {
public:
	PObject(glm::vec3 pos = { 0.0f, 0.0f, 0.0f });
	virtual ~PObject() override;

	void translate(glm::vec3 trans);
	void rotate(float angle, glm::vec3 axis, SPACE relativeTo); // Angle in radians, axis to rotate around, and relative space
	
	inline void setPosition(glm::vec3 pos) { position = pos; }

	inline const glm::vec3 &getPosition() const { return position; }

	const glm::vec3& getFront();
	const glm::vec3& getRight();
	const glm::vec3& getUp();

	inline void addComponent(COMPONENT_TYPE type, std::shared_ptr<Component> comp) { components[type] = comp; }

	void draw(const std::shared_ptr<Shader> shader);
protected:
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	static glm::vec3 worldUp; // this might not live here by the end, probably better to have it in a render class

	std::map<COMPONENT_TYPE, std::shared_ptr<Component>> components;

	virtual void updateVectors();
};

#endif // !POBJECTCLASS

