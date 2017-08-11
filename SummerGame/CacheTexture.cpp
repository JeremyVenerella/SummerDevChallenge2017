#include "CacheTexture.h"
#include "FileManager.h"
#include "Log.h"

CacheTexture::CacheTexture()
{
}


CacheTexture::~CacheTexture()
{
}

OGLTexture CacheTexture::getTexture(std::string fPath)
{
	std::map<std::string, OGLTexture>::iterator iterator =  _texture.find(fPath);
	//return loaded texture
	if (iterator == _texture.end())
	{
		OGLTexture loadedTexture = FileManager::loadPNG(fPath);
		_texture.insert(std::pair<std::string, OGLTexture>(fPath, loadedTexture));
		Log::write("Loaded a texture from file", Log::Info);
		return loadedTexture;
	}
	//return existing texture
	Log::write("Loaded a texture from cache", Log::Info);
	return iterator->second;
}
