#include "Renderer.h"

Renderer::Renderer()
{

}


Renderer::~Renderer()
{
}

void Renderer::render()
{
}

void Renderer::init(const char * title, int x, int y, int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
	{
		Log::write("SDL Window failed to create", Log::FatalError);
		SDL_Quit();
		exit(1);
	}
	
	SDL_GLContext glContex = SDL_GL_CreateContext(_window);
	if (glContex == nullptr)
	{
		Log::write(SDL_GetError(), Log::FatalError);

	}

	GLenum glError = glewInit();
	if (glError != GLEW_OK)
	{
		Log::write("GLEW failed to INIT", Log::FatalError);
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	//compile shaders
	_colorShaders.run("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorShaders.addAttrib("vertPos");
	_colorShaders.linkShader();

	_isRunning = true;
}

void Renderer::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		_isRunning = false;
		break;

	}
}

void Renderer::clean()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

bool Renderer::running()
{
	return _isRunning;
}

void Renderer::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorShaders.use();
	_sprite.draw();
	_colorShaders.unuse();

	SDL_GL_SwapWindow(_window);
}
