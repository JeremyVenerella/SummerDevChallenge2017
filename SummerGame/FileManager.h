#pragma once
#include <vector>
#include "OGLTexture.h"
#include <string>

class FileManager
{
public:
	static bool readFile(std::string filePath, std::vector<unsigned char> &buffer);
	static OGLTexture loadPNG(std::string filePath);
};

