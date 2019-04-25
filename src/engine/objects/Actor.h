#include "Object.h"

#ifndef ACTOR
#define ACTOR

class Actor : protected Object {
public:
	Actor();
	virtual ~Actor() override;
protected:
};


#endif // !ACTOR

