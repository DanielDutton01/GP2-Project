#include "Main_Game_Class.h"
#include <iostream>
#include <string>


Vertex_Class vertices[] = { Vertex_Class(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					Vertex_Class(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					Vertex_Class(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

Camera_Transform transform;
Camera_Transform npc_transform;

Main_Game_Class::Main_Game_Class()
{
	_gameState = GameState::PLAY;
	Game_Display_Class* _gameDisplay = new Game_Display_Class(); //new display
	Game_Mesh_Class* player();
	Game_Mesh_Class* npc();
	Game_Texture_Class* texture();
	Game_Shader_Class* shader();
	Game_Texture_Class* texture2();
	Game_Shader_Class* shader2();
}

Main_Game_Class::~Main_Game_Class()
{
}

void Main_Game_Class::run()
{
	initSystems();
	gameLoop();
}

bool Main_Game_Class::colCheck(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float dis = m1Rad + m2Rad;
	float totalD = glm::sqrt((m2Pos.x-m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (totalD <= dis)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Main_Game_Class::initSystems()
{
	_gameDisplay.initDisplay();

	myCamera.init_Game_Camera(glm::vec3(0, 0, -12), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);
	counterX = 0.0f;
	counterSpeed = 0.0f;

	//player starting information
	player.loadModel("..\\res\\monkey3.obj");
	texture.init("..\\res\\rainbow.png"); //
	shader.init("..\\res\\shader"); //new shader

	transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(sinf(1), sinf(1), sinf(1)));

	//npc starting info
	npc.loadModel("..\\res\\monkey3.obj");
	texture2.init("..\\res\\rainbow.png"); //
	shader2.init("..\\res\\shader"); //new shader

	npc_transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	npc_transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	npc_transform.SetScale(glm::vec3(sinf(1), sinf(1), sinf(1)));

}

void Main_Game_Class::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		update();
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




	if (npcPosY < 5)
	{
		npcPosX += sin(npcRot) * speed;
		npcPosY += cos(npcRot) * speed;
	}
	else if(npcPosY>=5 || npcPosY<=-6)
	{
		npcPosY = -1 * (rand()%5+1);
		npcPosX = 1 * (rand() % 5 + 1);
		
		if ((rand() % 2 + 1) == 1)
		{
			//npcPosY = npcPosY * -1;
			npcPosX = npcPosX * -1;
		}
	}


		npc_transform.SetRot(glm::vec3(0.0, 0.0, npcRot * -1));
		npc_transform.SetPos(glm::vec3(npcPosX, npcPosY, 0.0));

		//npcRot += 0.1;
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

void Main_Game_Class::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	player.draw();

	shader2.Bind();
	shader.Update(npc_transform, myCamera);
	texture2.Bind(0);
	npc.draw();
	
	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}