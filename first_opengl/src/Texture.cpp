#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<glad/glad.h>
Texture::Texture()
{
	
}

Texture::~Texture()
{
	
}

unsigned int Texture::load_texture(std::string filename) {

	if (texture_map[filename] == 0) {
		unsigned int id=0;
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			texture_map[filename] = id;
		}
		stbi_image_free(data);
		return id;
	}
	else {
		return texture_map[filename];
	}
	
}

void Texture::activatetexture(int level,unsigned int id) {
	glActiveTexture(level); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, id);
	
}