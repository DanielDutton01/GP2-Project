#include "Main_Game_Class.h"
#include <iostream>
#include <string>


Vertex_Class vertices[] = { Vertex_Class(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					Vertex_Class(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					Vertex_Class(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

Camera_Transform transform;
Camera_Transform obstacle_transform;
Camera_Transform planet_transform;

Main_Game_Class::Main_Game_Class()
{
	_gameState = GameState::PLAY;
	Game_Display_Class* _gameDisplay = new Game_Display_Class(); //new display
	Game_Mesh_Class* player();
	Game_Mesh_Class* npc();
	Game_Mesh_Class* planet();
	Game_Texture_Class* texture();
	Game_Shader_Class* shader();
	Game_Texture_Class* texture2();
	Game_Shader_Class* shader2();
	Game_Texture_Class* texture3();
	Game_Shader_Class* shader3();
	Game_Audio_Class* device();
}

Main_Game_Class::~Main_Game_Class()
{
}

void Main_Game_Class::run()
{
	initSystems();
	gameLoop();
}

void Main_Game_Class::initSystems()
{
	_gameDisplay.initDisplay();

	myCamera.init_Game_Camera(glm::vec3(0, 0, -12), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);
	counterX = 0.0f;
	counterSpeed = 0.0f;

	bkgMusic = device.loadSound("..\\res\\bkgMusic.wav");
	sfx = device.loadSound("..\\res\\hit.wav");

	//player starting information
	player.loadModel("..\\res\\Rocket.obj");
	texture.init("..\\res\\rainbow.png"); //
	shader.init("..\\res\\shader"); //new shader

	transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(sinf(1), sinf(1), sinf(1)));

	//obstacle starting info
	obstacle.loadModel("..\\res\\Rock.obj");
	texture2.init("..\\res\\rainbow.png"); //
	shader2.init("..\\res\\shader"); //new shader

	obstacle_transform.SetPos(glm::vec3(0.0, -5.0, 0.0));
	obstacle_transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	obstacle_transform.SetScale(glm::vec3(sinf(1), sinf(1), sinf(1)));
	obstaclePosY = -5;

	//planet starting info
	planet.loadModel("..\\res\\Planet.obj");
	texture3.init("..\\res\\rainbow.png"); //
	shader3.init("..\\res\\shader"); //new shader

	planet_transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	planet_transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	planet_transform.SetScale(glm::vec3(sinf(0.1), sinf(0.1), sinf(0.1)));

}

void Main_Game_Class::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		update();
		collision(player.getSpherePos(), player.getSphereRadius(), obstacle.getSpherePos(), obstacle.getSphereRadius());
		playAudio(bkgMusic, glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void Main_Game_Class::update()
{
	if (_gameState == GameState::FORWARD)// if key is pressed then move forward
	{
		playerPosX += sin((counterX)) * counterSpeed;
		playerPosY += cos((counterX)) * counterSpeed;

		transform.SetPos(glm::vec3(playerPosX, playerPosY, 0.0));
		counterSpeed = counterSpeed + 0.1f;
		if (counterSpeed > 0.1) { counterSpeed = 0.1; }
		//myCamera.init_Game_Camera(glm::vec3(playerPosX, playerPosY, -12), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f); //move cam with player
	}
	else if (_gameState == GameState::BACK)// if key is pressed then move back
	{
		playerPosX -= sin((counterX)) * -counterSpeed;
		playerPosY -= cos((counterX)) * -counterSpeed;
		
		transform.SetPos(glm::vec3(playerPosX, playerPosY, 0.0));
		counterSpeed = counterSpeed - 0.1f;
		if (counterSpeed < -0.1) { counterSpeed = -0.1; }
		//myCamera.init_Game_Camera(glm::vec3(playerPosX, playerPosY, -12), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f); //move cam with player
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

	player.updateSphereData(*transform.GetPos(), 0.5f);

	if (obstaclePosY < 5)
	{
		obstaclePosX += sin(obstacleRot) * speed;
		obstaclePosY += cos(obstacleRot) * speed;
	}
	else if(obstaclePosY>=5 || obstaclePosY<=-6)
	{
		obstaclePosY = -5;
		obstaclePosX = 1 * (rand() % 5 + 1);
		if ((rand() % 2 + 1) == 1)
		{
			obstaclePosX = obstaclePosX * -1;
		}
	}

	planetPosX += sin(planetRot) * 0.01;
	planetPosY += cos(planetRot) * 0.01;
	planetRot += 0.01;

		obstacle_transform.SetRot(glm::vec3(0.0, 0.0, obstacleRot * -1));
		obstacle_transform.SetPos(glm::vec3(obstaclePosX, obstaclePosY, 0.0));
		obstacle.updateSphereData(*obstacle_transform.GetPos(), 0.5f);

		planet_transform.SetRot(glm::vec3(planetRot * -1, planetRot * -1, 0.0));
		planet_transform.SetPos(glm::vec3(1+planetPosX, 2+planetPosX, 0.0));
		planet.updateSphereData(*planet_transform.GetPos(), 0.5f);
		
}

void Main_Game_Class::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
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
		case SDL_KEYUP:
			_gameState = GameState::PLAY;
				break;
		}
	}

}

bool Main_Game_Class::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		device.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		
		playAudio(sfx, m1Pos); //play collision audio
		
		//reset obstacle position
		obstaclePosY = -5;
		obstaclePosX = 1 * (rand() % 5 + 1);

		if ((rand() % 2 + 1) == 1)
		{
			obstaclePosX = obstaclePosX * -1;
		}
		
		return true;
	}
	else
	{
		return false;
	}
}

void Main_Game_Class::playAudio(unsigned int Source, glm::vec3 pos)
{

	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);

	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		device.playSound(Source, pos);
	}
}

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
	
	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}