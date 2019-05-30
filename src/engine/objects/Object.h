#include "../common/Includes.h"

#ifndef OBJECTCLASS
#define OBJECTCLASS

class Object {
public:
	Object();
	virtual ~Object();

protected:
	bool initialized = false;
};

#endif // !OBJECT

