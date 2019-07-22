#include "Includes.h"

#include "Glerror.h"

void GLGetError() {
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		LOG_ERROR("GLError::{0}", err);
	}
}