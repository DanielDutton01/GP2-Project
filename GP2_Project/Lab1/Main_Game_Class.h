#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Game_Display_Class.h" 
#include "Game_Shader_Class.h"
#include "Game_Mesh_Class.h"
#include "Game_Texture_Class.h"

enum class GameState { PLAY, EXIT };

class Main_Game_Class
{
public:
	Main_Game_Class();
	~Main_Game_Class();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();

	Game_Display_Class _gameDisplay;
	GameState _gameState;

	float counter;


};


