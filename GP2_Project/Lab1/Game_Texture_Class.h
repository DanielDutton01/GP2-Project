#pragma once
#include "stb_image.h"
#include <string>
#include <GL\glew.h>

class Game_Texture_Class
{
public:
	Game_Texture_Class();

	void Bind(unsigned int unit); // bind upto 32 textures
	void init(const std::string& fileName);
	void skyboxInit(const std::string fileName);

	~Game_Texture_Class();

	GLuint faces[5];

protected:
private:

	GLuint textureHandler;
	GLuint boxTexture;
};

