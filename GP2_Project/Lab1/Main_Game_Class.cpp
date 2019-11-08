#include "Main_Game_Class.h"
#include <iostream>
#include <string>


Vertex_Class vertices[] = { Vertex_Class(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					Vertex_Class(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					Vertex_Class(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

Camera_Transform transform;

Main_Game_Class::Main_Game_Class()
{
	_gameState = GameState::PLAY;
	Game_Display_Class* _gameDisplay = new Game_Display_Class(); //new display
	Game_Mesh_Class* mesh1();
	Game_Mesh_Class* mesh2();
	Game_Texture_Class* texture();
	Game_Shader_Class* shader();
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

	mesh2.loadModel("..\\res\\monkey3.obj");

	texture.init("..\\res\\bricks.jpg"); //
	shader.init("..\\res\\shader"); //new shader

	myCamera.init_Game_Camera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);
	counter = 0.0f;
}

void Main_Game_Class::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
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
		}
	}

}

void Main_Game_Class::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh2.draw();
	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}