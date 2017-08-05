#pragma once
#include "SDL.h"
#include "Renderer.h"

class Game
{
public:
	Game();
	~Game();

	void gameInit(const char * gameTitle);
	void update();
	bool running();

private:
	Renderer *renderer = new Renderer();
};

