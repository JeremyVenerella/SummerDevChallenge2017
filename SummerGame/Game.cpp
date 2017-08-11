#include "Game.h"


Game::Game()
{

}


Game::~Game()
{

}

void Game::gameInit(const char * gameTitle)
{
	_maxFps = 1005.0f;
	_renderer->init(gameTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);

	//loading sprite
	_renderer->addSprite(-1.0f, -1.0f, 1.0f, 1.0f, "Assets/astronaut_S.png");
	_renderer->addSprite(0.0f, -1.0f, 1.0f, 1.0f, "Assets/astronaut_S.png");

	loop();

}
//IO and draw updates
void Game::update()
{
	_renderer->handleEvents();
	_renderer->draw();
}

void Game::loop()
{
	while (running())
	{
		float startTicks = SDL_GetTicks();
		update();
		_renderer->timeStep();
		//cout FPS
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _renderer->fps() << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFps > frameTicks)
		{
			//SDL_Delay(1000.0f / _maxFps - frameTicks);
		}
	}
	_renderer->clean();
}

bool Game::running()
{
	return _renderer->running();
}
