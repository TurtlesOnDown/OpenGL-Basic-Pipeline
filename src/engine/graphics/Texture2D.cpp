#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

Texture2D::Texture2D(Path& p):path(p) {

}

Texture2D::~Texture2D() {

}

void Texture2D::init(int s, int t, int min, int mag) {
	if (initialized) return;
	glGenTextures(1, &texture);
	bind();
	// set the texture wrapping parameters
	setWrappingParam(s, t);
	// set texture filtering parameters
	setFilteringParam(min, mag);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	data = stbi_load(path.getPath().c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "TEXTURE::UNABLE TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);
	unbind();

	initialized = true;
}

/*void Texture2D::destroy() {

}*/

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

void Texture2D::activateTexure(unsigned int num) {
	glActiveTexture(GL_TEXTURE0 + num);
	bind();
}