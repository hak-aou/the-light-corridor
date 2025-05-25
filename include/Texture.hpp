#pragma once

#include <GL/gl.h>
#include <unordered_map>
#include <string>
#include <ostream>
#include <iostream>



extern std::unordered_map<std::string, GLuint> textures;

GLuint getTexture(std::string pathToTexture);
void freeAllTextures();