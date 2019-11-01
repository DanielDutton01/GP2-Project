#include "Main_Game_Class.h"
#include <iostream>
#include <string>

Main_Game_Class::Main_Game_Class()
{
	_gameState = GameState::PLAY;
	Game_Display_Class* _gameDisplay = new Game_Display_Class(); //new display
	counter = 0.0f;
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
	_gameDisplay.clearDisplay();

	Vertex_Class vertices[] = { Vertex_Class(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
							Vertex_Class(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
							Vertex_Class(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };
	Vertex_Class vertices1[] = { Vertex_Class(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
							Vertex_Class(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
							Vertex_Class(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

	Game_Mesh_Class mesh(vertices, sizeof(vertices) / sizeof(vertices[0])); //size calcuated by number of bytes of an array / no bytes of one element

	Game_Mesh_Class mesh1(vertices1, sizeof(vertices1) / sizeof(vertices1[0])); //size calcuated by number of bytes of an array / no bytes of one element

	Shader shader("..\\res\\shader"); //new shader
	Texture texture("..\\res\\bricks.jpg"); //load texture
	Texture texture1("..\\res\\water.jpg"); //load texture
	Transform transform;

	transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));

	shader.Bind();
	shader.Update(transform);
	texture.Bind(0);
	mesh.Draw();

	counter = counter + 0.01f;

	transform.SetPos(glm::vec3(-sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(-sinf(counter), -sinf(counter), -sinf(counter)));

	shader.Update(transform);
	texture1.Bind(0);
	mesh1.Draw();

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}