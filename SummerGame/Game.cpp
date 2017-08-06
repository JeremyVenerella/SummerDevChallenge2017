#include "Game.h"


Game::Game()
{
}


Game::~Game()
{

}

void Game::gameInit(const char * gameTitle)
{
	
	_renderer->init(gameTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);

	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
	_renderer->_sprite = _sprite;

	loop();

}

void Game::update()
{
	_renderer->handleEvents();
	_renderer->draw();
}

void Game::loop()
{
	while (running())
	{
		update();
	}
	_renderer->clean();
}

bool Game::running()
{
	return _renderer->running();
}
