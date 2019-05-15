#include "Object.h"
#include <glm/gtc/quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifndef POBJECT
#define POBJECT

enum class SPACE {WORLD, LOCAL};

class PObject : protected Object {
public:
	PObject(glm::vec3 pos = { 0.0f, 0.0f, 0.0f });
	virtual ~PObject() override;

	void translate(glm::vec3 trans);
	void rotate(float angle, glm::vec3 axis, SPACE relativeTo);

	inline const glm::vec3 &getPosition() const { return position; }

	const glm::vec3& getFront();
	const glm::vec3& getRight();
	const glm::vec3& getUp();
	
protected:
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 front = { 0.0f, 0.0f, 1.0f };
	glm::vec3 right;
	glm::vec3 up;
	static glm::vec3 worldUp; // this might not live here by the end, probably better to have it in a render class

	bool updated = false;

	virtual void updateVectors();
};

#endif // !ACTOR

