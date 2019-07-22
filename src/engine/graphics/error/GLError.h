#pragma once

#define DEBUG

void GLGetError();

#ifdef DEBUG
#define GLGET_ERROR GLGetError

#else
#define GLGET_ERROR

#endif // DEBUG

 