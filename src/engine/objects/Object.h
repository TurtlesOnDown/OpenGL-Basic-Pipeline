#pragma once

#include "Includes.h"

#include "../core/events/Event.h"

class Object {
public:
	Object();
	virtual ~Object();

	virtual void onUpdate() = 0;
	virtual void onEvent(Event &e) = 0;

protected:
	bool initialized = false;
};


