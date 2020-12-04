#include "Game.h"

int main() 
{
	Game* app = new Game();

	app->run();

	delete app;

	return 0;
}