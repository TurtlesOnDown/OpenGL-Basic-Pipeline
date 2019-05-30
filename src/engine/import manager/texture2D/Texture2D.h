#include "../../common/Includes.h"

#include "../../common/Path.h"
#include "../../objects/Component.h"

#ifndef TEXTURE2DCLASS
#define TEXTURE2DCLASS

/*
A class for loading and using 2D textures

How to use:
activateTexture(i);
shader->setInt(textureName, i);
bind();
*/

class Texture2D : public Component {
public:
	Texture2D(Path& p);
	~Texture2D();

	void bind();
	void unbind();
	void setWrappingParam(int s = GL_MIRRORED_REPEAT, int t = GL_MIRRORED_REPEAT);
	void setFilteringParam(int min = GL_NEAREST, int mag = GL_LINEAR);
	void genMipMaps();

	void activateTexture(unsigned int num);

	inline unsigned int getOpenGLID() const { return texture; };

private:
	int width, height, nrChannels;
	unsigned int texture;
	Path path;

	friend class Texture2DImporter;
};

class ImportManager;

class Texture2DImporter {
public:
	Texture2DImporter(ImportManager* imp);
	~Texture2DImporter();

	std::shared_ptr<Texture2D> load(Path& p);
private:
	std::map<std::string, std::shared_ptr<Texture2D>> textures;
	ImportManager *manager;

	void importTexture(std::shared_ptr<Texture2D> texture);
};

#endif // !TEXTURE

