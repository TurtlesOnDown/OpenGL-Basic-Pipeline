#include "Includes.h"

#include "Object.h"

#ifndef COMPONENTCLASS
#define COMPONENTCLASS

// Component class base type
// Components are classes that attach to objects that have one instance shared between multiple pobjects

enum class COMPONENT_TYPE {
	MESH,
	MODEL,
	MATERIAL,
	SHADER,
	TEXTURE2D
};

class Component : public Object {
public:
	Component(COMPONENT_TYPE t);
	virtual ~Component() override;

protected:
	const COMPONENT_TYPE type;
};

#endif // !COMPONENT

