#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Game_Display_Class
{
public:
	Game_Display_Class();
	~Game_Display_Class();
	void initDisplay();
	void swapBuffer();
	void clearDisplay();

private:

	void returnError(std::string errorString);

	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	int screenWidth;
	int screenHeight;
};

