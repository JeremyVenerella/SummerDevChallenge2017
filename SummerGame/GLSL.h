#pragma once
#include "GL\glew.h"
#include<string>

class GLSL
{
public:
	GLSL();
	~GLSL();

	void run(const std::string& vertPath, const std::string& fragPath);
	void compileShader(const std::string& filePath, GLuint id);
	void linkShader();
	void addAttrib(const std::string& attribName);
	void use();
	void unuse();

private:
	GLuint _programID;
	GLuint _vertexShaerID;
	GLuint _fragmentShaderID;
	int _numAttrib;
};

