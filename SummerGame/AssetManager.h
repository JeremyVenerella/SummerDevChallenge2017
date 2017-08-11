#pragma once
#include "CacheTexture.h"
#include <string>

class AssetManager
{
public:
	static OGLTexture getTexture(std::string fPath);
private:
	static CacheTexture _cacheTexture;
};

