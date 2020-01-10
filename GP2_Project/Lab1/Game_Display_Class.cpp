#include "Game_Display_Class.h"
//initialises variables
Game_Display_Class::Game_Display_Class()
{
	sdlWindow = nullptr; //initialise to generate null access violation for debugging. 
	screenWidth = 1024.0f;
	screenHeight = 768.0f;
}

Game_Display_Class::~Game_Display_Class()
{
	SDL_GL_DeleteContext(glContext); // delete context
	SDL_DestroyWindow(sdlWindow); // detete window (make sure to delete the context and the window in the opposite order of creation in initDisplay())
	SDL_Quit(); //quits
}
//gets the screen width and returns it
float Game_Display_Class::getWidth()
{
	return screenWidth;
}
//gets the screen width and returns it
float Game_Display_Class::getHeight()
{
	return screenHeight;
}
//checks for error and reports if any occurs, then quits if so
void Game_Display_Class::returnError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void Game_Display_Class::swapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow); //swap buffers
}
//clears the display
void Game_Display_Class::clearDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}
//initalises the display
void Game_Display_Class::initDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL); // create window
	//set error if window doesn't exist
	if (sdlWindow == nullptr)
	{
		returnError("window failed to create");
	}

	glContext = SDL_GL_CreateContext(sdlWindow);
	//set error if context doesn't exist
	if (glContext == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	//set error if GLEW doesn't initialise
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //sets the clear value for buffers
}
