#include "Game_Texture_Class.h"
#include <cassert>
#include <iostream>

Game_Texture_Class::Game_Texture_Class()
{
}

void Game_Texture_Class::init(const std::string& fileName)
{
	int width, height, numComponents; //width, height, and no of components of image
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4); //load the image and store the data

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	glGenTextures(1, &textureHandler); // number of and address of textures
	glBindTexture(GL_TEXTURE_2D, textureHandler); //bind texture - define type 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data

	stbi_image_free(imageData);

}


//attempt at creating skybox
/*
void Game_Texture_Class::skyboxInit(const std::string fileName)
{
	int width, height, numComponents; //width, height, and no of components of image
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4); //load the image and store the data

	//sends error message if image is not found
	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}
	
	glGenTextures(1, &boxTexture); //number of and address of cube map

	glBindTexture(GL_TEXTURE_CUBE_MAP, boxTexture); //bind texture

	glTexStorage2D(GL_TEXTURE_CUBE_MAP, 0, GL_RGB,
		width, height);
	//goes through each of the 6 faces applying an image
	for (int face = 0; face < 6; face++)
	{
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}

	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	stbi_image_free(imageData);
}
*/

Game_Texture_Class::~Game_Texture_Class()
{
	glDeleteTextures(1, &textureHandler); // number of and address of textures
}

void Game_Texture_Class::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); /// check we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + unit); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, textureHandler); //type of and texture to bind to unit
}