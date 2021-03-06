#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include "../../import manager/ImportManager.h"

Texture2D::Texture2D(Path& p):Component(COMPONENT_TYPE::TEXTURE2D), path(p) {
	glGenTextures(1, &texture);
}

Texture2D::~Texture2D() {

}

void Texture2D::bind() {
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture2D::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setWrappingParam(int s, int t) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

void Texture2D::setFilteringParam(int min, int mag) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

void Texture2D::genMipMaps() {
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::activateTexture(unsigned int num) {
	glActiveTexture(GL_TEXTURE0 + num);
	bind();
}

Texture2DImporter::Texture2DImporter(ImportManager* imp):manager(imp) {

}

Texture2DImporter::~Texture2DImporter() {

}

std::shared_ptr<Texture2D> Texture2DImporter::load(Path& p) {
	if (textures.find(p.getPath()) != textures.end()) {
		return textures[p.getPath()];
	}

	std::shared_ptr<Texture2D> ret = std::shared_ptr<Texture2D>(new Texture2D(p));
	importTexture(ret);
	textures[p.getPath()] = ret;
	return std::shared_ptr<Texture2D>(textures[p.getPath()]);
}

void Texture2DImporter::importTexture(std::shared_ptr<Texture2D> texture) {

	texture->bind();

	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	uint8_t* data = stbi_load(texture->path.getPath().c_str(), &texture->width, &texture->height, &texture->nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (texture->nrChannels == 1)
			format = GL_RED;
		else if (texture->nrChannels == 3)
			format = GL_RGB;
		else if (texture->nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, data);
		texture->setWrappingParam();
		texture->setFilteringParam();
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "TEXTURE::UNABLE TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);

	texture->unbind();
}