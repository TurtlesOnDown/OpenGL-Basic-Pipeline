#include "Includes.h"

#include "ImportManager.h"

ImportManager ImportManager::resourceManager;

ImportManager::ImportManager():
	models(this),
	textures2D(this) ,
	shaders(this)
{

}

ImportManager::~ImportManager() {

}