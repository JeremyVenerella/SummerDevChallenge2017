#pragma once
#include <GL/glew.h>
#include "OGLTexture.h"
#include <string>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string tPath);

	void draw();

private:
	float _x;
	float _y;
	float _width;
	float _height;
	GLuint _vboID;
	OGLTexture _texture;
};

