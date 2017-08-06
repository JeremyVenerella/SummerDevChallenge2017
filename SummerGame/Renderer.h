#pragma once
#include "SDL.h"
#include "GL/glew.h"
#include "Log.h"
#include "Sprite.h"
#include "GLSL.h"

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
	void draw();

	Sprite _sprite;
	
private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	bool _fullScreen = false;
	bool _isRunning;
	GLSL _colorShaders;
};

