#include "Renderer.h"


Renderer::Renderer()
{

}


Renderer::~Renderer()
{
}

void Renderer::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Renderer::init(const char * title, int x, int y, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, x, y, width, height, fullScreen);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

void Renderer::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	}
}

void Renderer::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Renderer::running()
{
	return isRunning;
}
