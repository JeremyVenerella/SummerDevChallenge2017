#pragma once
#include <map>
#include "OGLTexture.h"
class CacheTexture
{
public:
	CacheTexture();
	~CacheTexture();
	OGLTexture getTexture(std::string fPath);

private:
	std::map<std::string, OGLTexture> _texture;
};

