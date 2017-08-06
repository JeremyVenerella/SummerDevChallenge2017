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
		_log.write("SDL Window failed to create", _log.FatalError);
		SDL_Quit();
		exit(1);
	}
	
	SDL_GLContext glContex = SDL_GL_CreateContext(_window);
	if (glContex == nullptr)
	{
		_log.write(SDL_GetError(), _log.FatalError);
		SDL_Quit();
		exit(1);
	}

	GLenum glError = glewInit();
	if (glError != GLEW_OK)
	{
		_log.write("GLEW failed to INIT", _log.FatalError);
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

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

	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(0, 300);
	glVertex2f(300, 300);
	glEnd();

	SDL_GL_SwapWindow(_window);
}
