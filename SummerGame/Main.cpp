#include "Game.h"

int main(int argc, char* argv[])
{
	Game *game = new Game();
	game->gameInit("Summer Game");

	while (game->running())
	{
		game->update();
	}
	game->~Game();
	return 0;
}