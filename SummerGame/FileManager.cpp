#include "FileManager.h"
#include <fstream>
#include "picoPNG.h"
#include "Log.h"


bool FileManager::readFile(std::string filePath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		Log::write("Failed to load file "+ filePath, Log::Warning);
		return false;
	}
	//get file size
	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	//remove the header
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);
	return true;
}

OGLTexture FileManager::loadPNG(std::string filePath)
{
	OGLTexture texture = {};

	std::vector<unsigned char> out_img;
	unsigned long image_width, image_height;
	std::vector<unsigned char> in_img;

	if (!readFile(filePath, in_img))
		Log::write("Failed to read PNG " + filePath, Log::Warning);

	int err = decodePNG(out_img, image_width, image_height, &(in_img[0]), in_img.size());
	if (err != 0)
		Log::write("decodePNG failed, Code: " + err, Log::FatalError);
	//gen texture and bind
	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out_img[0]));
	//parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//gen the mip map
	glGenerateMipmap(GL_TEXTURE_2D);
	
	//unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.w = image_width;
	texture.h = image_height;
	return texture;
}
