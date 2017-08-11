#include "AssetManager.h"

CacheTexture AssetManager::_cacheTexture;

OGLTexture AssetManager::getTexture(std::string fPath)
{
	return _cacheTexture.getTexture(fPath);
}
