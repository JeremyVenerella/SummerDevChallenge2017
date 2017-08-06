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
	void loop();
	bool running();

private:
	Renderer *_renderer = new Renderer();
};

