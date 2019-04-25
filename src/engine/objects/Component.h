#include "Object.h"

#ifndef COMPONENT
#define COMPONENT

class Component : public Object {
public:
	Component();
	virtual ~Component() override;
protected:
};

#endif // !COMPONENT

