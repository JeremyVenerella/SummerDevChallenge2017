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
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	if (_window == nullptr)
	{
		Log::write("SDL Window failed to create", Log::FatalError);
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


	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	SDL_GL_SetSwapInterval(0);//VSYNC ON[1]/OFF[0]

	//compile shaders
	_colorShaders.run("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorShaders.addAttrib("vertPos");
	_colorShaders.addAttrib("vertexColor");
	_colorShaders.addAttrib("vertexUV");
	_colorShaders.linkShader();

	//TODO: REMOVE 
	//_pTexture = FileManager::loadPNG("Assets/astronaut_S.png");


	//Check the OGL version
	_glVersion = (char*)glGetString(GL_VERSION);
	std::printf(" %s \n", _glVersion);

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
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorShaders.getUniformLocation("samp2d");
	glUniform1i(textureLocation, 0);

	//GLint timeLoc = _colorShaders.getUniformLocation("time");
	//glUniform1f(timeLoc, _time);

	//draw all sprites
	for (auto &v : _sprites)
	{
		v->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorShaders.unuse();

	SDL_GL_SwapWindow(_window);
}

void Renderer::addSprite(float x, float y, float width, float height, std::string tPath)
{
	_sprites.push_back(new Sprite());
	_sprites.back()->init(x, y, width, height, tPath);
}

float Renderer::fps()
{
	static const int samples = 10;
	static float frameTime[samples];
	static int currentFrame = 0;
	static float previous = SDL_GetTicks();
	float current;
	current = SDL_GetTicks();
	
	_frameTime = current - previous;
	frameTime[currentFrame % samples] = _frameTime;
	previous = current;

	int count;
	currentFrame++;

	if (currentFrame < samples)
	{
		count = currentFrame;
	}
	else
	{
		count = samples;
	}


	float frameAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameAverage += frameTime[i];
	}
	frameAverage /= count;
	if (frameAverage > 0)
	{
		_fps = 1000.0f / frameAverage;
	}
	else
	{
		_fps = 60.0f;
	}

	return _fps;
}
