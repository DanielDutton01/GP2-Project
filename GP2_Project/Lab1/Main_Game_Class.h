#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Game_Display_Class.h" 
#include "Game_Shader_Class.h"
#include "Game_Mesh_Class.h"
#include "Game_Texture_Class.h"
#include "Game_Camera.h"
#include "Game_Camera_Transform.h"
#include "Game_Audio_Class.h"

enum class GameState { PLAY, EXIT, FORWARD, BACK, RIGHT, LEFT};

class Main_Game_Class
{
public:
	Main_Game_Class();
	~Main_Game_Class();
	
	//variable that runs the game
	void run();

	//the transforms of the various models
	Camera_Transform transform;
	Camera_Transform obstacle_transform;
	Camera_Transform planet_transform;

private:
	//all the private functions used 
	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void Update();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void respawn(bool player, bool planet, bool obstacle);
	void playAudio(unsigned int Source, glm::vec3 pos);
	
	Game_Display_Class _gameDisplay;
	GameState _gameState;
	Game_Camera myCamera;

	//from skybox attempt
	/*
	Game_Mesh_Class skybox;
	Game_Texture_Class skyboxTex;
	Game_Shader_Class skyShader;
	*/

	//the variable for models, model positions/rotation/scale, textures, shaders and sounds

	Game_Mesh_Class player;
	Game_Texture_Class texture;
	Game_Shader_Class shader;
	Game_Audio_Class device;

	unsigned int sfx;
	unsigned int bkgMusic;

	float playerPosX;
	float playerPosY;
	float playerRot;
	float playerScale;

	float speed = 0.1;

	Game_Mesh_Class obstacle;
	Game_Texture_Class texture2;
	Game_Shader_Class shader2;

	float obstaclePosX;
	float obstaclePosY;
	float obstaclePosZ;
	float obstacleRot;
	float obstacleScale;
	int randDir = 1;

	Game_Mesh_Class planet;
	Game_Texture_Class texture3;
	Game_Shader_Class shader3;

	float planetPosX;
	float planetPosZ;
	float planetRot;
	float planetOrbit;
	float planetScale;

	float counterX;
	float counterSpeed;
};
