#include "GLSL.h"
#include "Log.h"
#include <fstream>
#include <vector>

GLSL::GLSL() : _programID(0), _vertexShaerID(0), _fragmentShaderID(0), _numAttrib(0)
{
}

GLSL::~GLSL()
{
}

void GLSL::run(const std::string& vertPath,const std::string& fragPath)
{
	//Get a program object.
	_programID = glCreateProgram();

	//create an instance of the shaders
	_vertexShaerID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaerID == 0)
		Log::write("Failed to create vertex shader", Log::FatalError);
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
		Log::write("Failed to create fragment shader", Log::FatalError);
	
	//compile
	compileShader(vertPath, _vertexShaerID);
	compileShader(fragPath, _fragmentShaderID);
}

void GLSL::compileShader(const std::string& filePath, GLuint id)
{

	//read vertex shader file
	std::ifstream vertexfile(filePath);
	if (vertexfile.fail())
		Log::write((filePath.c_str()), Log::FatalError);
	
	std::string file = "";
	std::string line;

	while (std::getline(vertexfile, line))
	{
		file += line + "\n";
	}
	vertexfile.close();
	//compile shader
	const char* filePtr = file.c_str();
	glShaderSource(id, 1, &filePtr, nullptr);
	glCompileShader(id);
	//return errors of comilation
	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		Log::write(&(errorLog[0]), Log::FatalError);
	}

}

void GLSL::linkShader()
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.


	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaerID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength+1);
		glGetProgramInfoLog(_programID, maxLength+1, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaerID);
		glDeleteShader(_fragmentShaderID);


		Log::write(&(infoLog[0]), Log::FatalError);
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaerID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaerID);
	glDeleteShader(_fragmentShaderID);
}

void GLSL::addAttrib(const std::string & attribName)
{

	glBindAttribLocation(_programID, _numAttrib, attribName.c_str());
	++_numAttrib;
}

void GLSL::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttrib; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSL::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttrib; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLint GLSL::getUniformLocation(const std::string & name)
{
	GLint uLoc = glGetUniformLocation(_programID, name.c_str());
	if (uLoc == GL_INVALID_INDEX)
		Log::write(name.c_str(), Log::FatalError);
	return uLoc;
}
