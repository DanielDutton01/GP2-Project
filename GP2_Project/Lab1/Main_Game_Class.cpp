#include "Main_Game_Class.h"
#include <iostream>
#include <string>

Main_Game_Class::Main_Game_Class()
{
	//variables are initialised appropriately
	_gameState = GameState::PLAY; //state is set to play
	Game_Display_Class* _gameDisplay = new Game_Display_Class(); //new display
	//models, textures, shaders and audio
	Game_Mesh_Class* player();
	Game_Mesh_Class* npc();
	Game_Mesh_Class* planet();
	Game_Texture_Class* texture();
	Game_Shader_Class* shader();
	Game_Texture_Class* texture2();
	Game_Shader_Class* shader2();
	Game_Texture_Class* texture3();
	Game_Shader_Class* shader3();
	//attempted skybox
	/*Game_Mesh_Class* skybox();
	Game_Texture_Class* skyboxTex();
	Game_Shader_Class* skyShader();*/
	Game_Audio_Class* device();
}

Main_Game_Class::~Main_Game_Class()
{
}

//runs the game
void Main_Game_Class::run()
{
	initSystems();
	gameLoop();
}

void Main_Game_Class::initSystems()
{
	_gameDisplay.initDisplay(); //initalises the display

	myCamera.init_Game_Camera(glm::vec3(0, 0, -12), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);
	//starts the speeds for the models
	counterX = 0.0f; 
	counterSpeed = 0.0f;
	//sets the audio to the appropriate files
	bkgMusic = device.loadSound("..\\res\\bkgMusic.wav");
	sfx = device.loadSound("..\\res\\hit.wav");

	//player starting information is set
	player.loadModel("..\\res\\Rocket.obj");
	texture.init("..\\res\\metal.png"); //
	shader.init("..\\res\\shader"); //new shader
	//sets models starting position, rotation & scale
	transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(sinf(1), sinf(1), sinf(1)));

	//obstacle starting info is set
	obstacle.loadModel("..\\res\\Rock.obj");
	texture2.init("..\\res\\rock.png"); //
	shader2.init("..\\res\\shader"); //new shader
	//sets models starting position, rotation & scale
	obstacle_transform.SetPos(glm::vec3(0.0, -5.0, 0.0));
	obstacle_transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	obstacle_transform.SetScale(glm::vec3(sinf(1), sinf(1), sinf(1)));
	obstaclePosY = -5;

	//planet starting info is set
	planet.loadModel("..\\res\\Planet.obj");
	texture3.init("..\\res\\planet.png"); //
	shader3.init("..\\res\\shader"); //new shader
	//sets models starting position, rotation & scale
	planet_transform.SetPos(glm::vec3(-3.4, 0.0, 0.0));
	planet_transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	planet_transform.SetScale(glm::vec3(sinf(0.1), sinf(0.1), sinf(0.1)));
	
	//Part of attempted skybox
	/*
	skybox.loadModel("..\\res\\cube.obj");
	skyboxTex.skyboxInit("..\\res\\world.png");
	skyShader.init("..\\res\\skyboxshader");
	*/

}

void Main_Game_Class::gameLoop()
{
	//enusres all necessary parts are used when game is running
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		Update();
		collision(player.getSpherePos(), player.getSphereRadius(), obstacle.getSpherePos(), obstacle.getSphereRadius());
		collision(planet.getSpherePos(), planet.getSphereRadius(), obstacle.getSpherePos(), obstacle.getSphereRadius());
		playAudio(bkgMusic, glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void Main_Game_Class::Update()
{
	if (_gameState == GameState::FORWARD)// if key is pressed then move forward
	{
		//move player based on their rotation and the speed it goes at
		playerPosX += sin((counterX)) * counterSpeed;
		playerPosY += cos((counterX)) * counterSpeed;
		//uses the variables to actually transform the player position
		transform.SetPos(glm::vec3(playerPosX, playerPosY, 0.0));
		//increase speed in positive direction, but not higher than a set max
		counterSpeed = counterSpeed + 0.1f;
		if (counterSpeed > 0.1) { counterSpeed = 0.1; }
	}
	else if (_gameState == GameState::BACK)// if key is pressed then move back
	{
		//move player based on their rotation and the speed it goes at
		playerPosX -= sin((counterX)) * -counterSpeed;
		playerPosY -= cos((counterX)) * -counterSpeed;
		//uses the variables to actually transform the player position
		transform.SetPos(glm::vec3(playerPosX, playerPosY, 0.0));
		//increase speed in positive direction, but not higher than a set max
		counterSpeed = counterSpeed - 0.1f;
		if (counterSpeed < -0.1) { counterSpeed = -0.1; }
	}
	else if (_gameState == GameState::LEFT)// if key is pressed then turn left
	{
		transform.SetRot(glm::vec3(0.0, 0.0, counterX * -1));
		counterX = counterX + 0.1f;
	}
	else if (_gameState == GameState::RIGHT)// if key is pressed then turn right
	{
		transform.SetRot(glm::vec3(0.0, 0.0, counterX * -1));
		counterX = counterX - 0.1f;
	}
	//updates the sphere data for the player to ensure colision detection
	player.updateSphereData(*transform.GetPos(), 0.5f);
	//moves the obstacle via the Y/Z as long as it is within the appropriate boundries
	if (obstaclePosY < 6 && obstaclePosZ < 6)
	{
		if (randDir == 1) 
		{
			obstaclePosY += speed;
		}
		else
		{
			obstaclePosZ += speed;
		}
	}
	else if(obstaclePosY>=5 || obstaclePosY<=-6 || obstaclePosZ >= 5 || obstaclePosZ <= -6)
	{
		respawn(false,false,true); //respawns obstacle if it leaves certain boundries
	}
	//rotates the obstacle for asthetic purposes
	obstacleRot += 0.1;

	//moves the planet around in an orbit while also rotating the planet itself
	planetPosX += sin(planetOrbit) * 0.01;
	planetPosZ += cos(planetOrbit) * 0.01;
	planetOrbit += 0.003;
	planetRot += 0.01;

	//where the movement for the obstacle is actually set, using the previously created values
	//and updates it's sphere data for colisions
	obstacle_transform.SetRot(glm::vec3(0.0, 0.0, obstacleRot * -1));
	obstacle_transform.SetPos(glm::vec3(obstaclePosX, obstaclePosY, obstaclePosZ));
	obstacle.updateSphereData(*obstacle_transform.GetPos(), 0.5f);
	//where the movement for the planet is actually set, using the previously created values
	//and updates it's sphere data for colisions
	planet_transform.SetRot(glm::vec3(planetRot * -1, planetRot * -1, 0.0));
	planet_transform.SetPos(glm::vec3(-3.4+planetPosX, 0.0, planetPosZ));
	planet.updateSphereData(*planet_transform.GetPos(), 0.5f);
		
}

void Main_Game_Class::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT: //quits the game
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN: //gets key inputs for movements
			if (evnt.key.keysym.sym == SDLK_w)
			{
				_gameState = GameState::FORWARD;
			}
			if (evnt.key.keysym.sym == SDLK_s)
			{
				_gameState = GameState::BACK;
			}
			if (evnt.key.keysym.sym == SDLK_a)
			{
				_gameState = GameState::LEFT;
			}
			if (evnt.key.keysym.sym == SDLK_d)
			{
				_gameState = GameState::RIGHT;
			}
				break;
		case SDL_KEYUP: //sets game back to default state
			_gameState = GameState::PLAY;
				break;
		}
	}

}

bool Main_Game_Class::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	//distance equation
	float distance = glm::sqrt((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));
	//checks the distance between the 2 models and if they are in colision range then audio is played and the models are reset
	if (distance < (m1Rad + m2Rad))
	{
		device.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		
		playAudio(sfx, m1Pos); //play collision audio
		//ensures only certain objects are respawned, specifically the obstacle and what it
		//colides with

			if (m1Pos.x == playerPosX && m1Pos.y == playerPosY)
			{
				respawn(true, false, true);
			}
			else if (m1Pos.x == planetPosX && m1Pos.z == planetPosZ)
			{
				respawn(false, true, true);
			}

		return true;
	}
	else
	{
		return false;
	}
}

void Main_Game_Class::respawn(bool playerRespawn, bool planetRespawn, bool obstacleRespawn)
{
		//respawns the obstacle to a random position on screen
	if (obstacleRespawn == true)
	{
		randDir = (rand() % 2 + 1);
		if (randDir == 1) //respawn for traveling the Y-axis
		{
			obstaclePosY = -5;
			obstaclePosZ = 0;
		}
		else //respawn for travelling the Z-axis
		{
			obstaclePosZ = -5;
			obstaclePosY = 1 * (rand() % 5 + 1);
			if ((rand() % 2 + 1) == 1) //decides, randomly, if the y position is at the top or bottom
			{
				obstaclePosY = obstaclePosY * -1;
			}
		}
		obstaclePosX = 1 * (rand() % 5 + 1);
		if ((rand() % 2 + 1) == 1) //decides, randomly, if the x position will be at the right or left
		{
			obstaclePosX = obstaclePosX * -1;
		}
	}
	//respawns the player at its origin point and resets the rotation
	if (playerRespawn == true)
	{
		transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
		playerPosX = 0;
		playerPosY = 0;
		transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
		counterX = 0;
	}
	//repsawns the planet at its origin point and resets its orbit
	if (planetRespawn == true)
	{
		planet_transform.SetPos(glm::vec3(-3.4, 0.0, 0.0));
		planetPosX = 0;
		planetPosZ = 0;
		planetOrbit = 0;
	}
}
//plays sounds
void Main_Game_Class::playAudio(unsigned int Source, glm::vec3 pos)
{
	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);

	if (AL_PLAYING != state)
	{
		device.playSound(Source, pos);
	}
}
//draw the game to the screen/display
void Main_Game_Class::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	player.draw();

	shader2.Bind();
	shader.Update(obstacle_transform, myCamera);
	texture2.Bind(0);
	obstacle.draw();

	shader3.Bind();
	shader.Update(planet_transform, myCamera);
	texture3.Bind(0);
	planet.draw();

	//atempt from skybox
	/*
	skyShader.Bind();
	skyShader.Update(transform, myCamera);
	skyboxTex.Bind(0);
	skybox.draw();
	*/

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}