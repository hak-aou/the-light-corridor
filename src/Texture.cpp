#include "../include/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

std::unordered_map<std::string, GLuint> textures;

GLuint getTexture(std::string pathToTexture) {
    auto it = textures.find(pathToTexture);
    if(it != textures.end()) {
        return it->second;
    }
    
    GLuint textureID;
	unsigned char *pixels_data;

	int x = 0;
	int y = 0;
	int n = 0;
	const char *image = pathToTexture.c_str();
	pixels_data = stbi_load(image, &x, &y, &n, 4); // 4 because we have 4 channels RGB and A for opacity

	if (pixels_data == NULL)
	{
		std::cout << "Probleme lors du chargement de l'image : " << image << std::endl;
        return 0;
    }

    glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
				 x, y, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, pixels_data);
	glBindTexture(GL_TEXTURE_2D, 0);

    textures[pathToTexture] = textureID;
	stbi_image_free(pixels_data);

    return textureID;
}


void freeAllTextures() {
	for (const auto& pair : textures)
	{
		glDeleteTextures(1, &pair.second);
	}
}