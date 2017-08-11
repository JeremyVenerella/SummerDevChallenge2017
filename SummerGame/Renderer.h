#pragma once
#include "SDL.h"
#include "GL/glew.h"
#include "Log.h"
#include "Sprite.h"
#include "GLSL.h"
#include "OGLTexture.h"
#include <vector>

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
	void addSprite(float x, float y, float width, float height, std::string tPath);
	float getTime() { return _time; };
	void timeStep() { _time += 0.01f; };
	float fps();
	
private:
	char* _glVersion;
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	bool _fullScreen = false;
	bool _isRunning;
	GLSL _colorShaders;
	float _time;
	float _fps;
	float _frameTime;
	std::vector<Sprite*> _sprites;
};

