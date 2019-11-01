#pragma once
#include <string>
#include <GL\glew.h>
#include "Game_Camera_Transform.h"

class Game_Shader_Class
{
public:
	Game_Shader_Class(const std::string& filename);

	void Bind(); //Set gpu to use our shaders
	void Update(const Camera_Transform& transform);

	std::string Game_Shader_Class::LoadShader(const std::string& fileName);
	void Game_Shader_Class::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint Game_Shader_Class::CreateShader(const std::string& text, unsigned int type);

	~Game_Shader_Class();


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};

