#include <iostream>
#include "Main_Game_Class.h"
//enterance into the program
int main(int argc, char** argv) //argument used to call SDL main
{
	Main_Game_Class mainGame;
	mainGame.run(); //starts running the game

	return 0;
}