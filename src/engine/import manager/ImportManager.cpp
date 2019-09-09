#include "Includes.h"

#include "ImportManager.h"

std::unique_ptr<ImportManager> ImportManager::resourceManager = std::make_unique<ImportManager>();

ImportManager::ImportManager():
	models(this),
	textures2D(this) ,
	shaders(this)
{

}

ImportManager::~ImportManager() {

}