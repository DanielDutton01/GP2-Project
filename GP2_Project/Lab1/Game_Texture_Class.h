#pragma once
#include "stb_image.h"
#include <string>
#include <GL\glew.h>

class Game_Texture_Class
{
public:
	Game_Texture_Class(const std::string& fileName);

	void Bind(unsigned int unit); // bind upto 32 textures

	~Game_Texture_Class();

protected:
private:

	GLuint textureHandler;
};

