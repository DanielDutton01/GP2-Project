#pragma once
#include "stb_image.h"
#include <string>
#include <GL\glew.h>

class Game_Texture_Class
{
public:
	Game_Texture_Class();

	void Bind(unsigned int unit); // bind upto 32 textures
	void init(const std::string& fileName); //initialises textures

	//void skyboxInit(const std::string fileName); //attempt at creating skybox
	//GLuint faces[5]; //attempt at creating skybox

	~Game_Texture_Class();

protected:
private:

	GLuint textureHandler;
	//GLuint boxTexture; //attempt at creating skybox
};

