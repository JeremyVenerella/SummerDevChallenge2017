#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
	renderer->clean();
}

void Game::gameInit(const char * gameTitle)
{
	
	renderer->init(gameTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
}

void Game::update()
{
	renderer->handleEvents();
	renderer->render();
}

bool Game::running()
{
	return renderer->running();
}
