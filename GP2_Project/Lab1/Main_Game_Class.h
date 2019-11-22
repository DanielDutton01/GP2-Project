#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Game_Display_Class.h" 
#include "Game_Shader_Class.h"
#include "Game_Mesh_Class.h"
#include "Game_Texture_Class.h"
#include "Game_Camera_Transform.h"

enum class GameState { PLAY, EXIT, FORWARD, BACK, RIGHT, LEFT};

class Main_Game_Class
{
public:
	Main_Game_Class();
	~Main_Game_Class();

	void run();
	bool colCheck(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();

	Game_Display_Class _gameDisplay;
	GameState _gameState;
	Game_Mesh_Class mesh1;
	Game_Mesh_Class mesh2;
	Game_Camera myCamera;
	Game_Texture_Class texture;
	Game_Shader_Class shader;


	float counter;
};


