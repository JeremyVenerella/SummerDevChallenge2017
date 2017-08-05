#pragma once
#include "SDL.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void render();
	void init(const char* title, int x, int y, int width, int height);
	void handleEvents();
	void clean();
	bool running();
	
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool fullScreen = false;
	bool isRunning;
};

