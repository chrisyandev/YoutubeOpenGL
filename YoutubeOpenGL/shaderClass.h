#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	/* Reference ID of the Shader Program. */
	GLuint ID;
	/* Builds the Shader Program from two different shaders. */
	Shader(const char* vertexFile, const char* fragmentFile);

	/* Activates the Shader Program. */
	void Activate();
	/* Deletes the Shader Program. */
	void Delete();

private:
	/* Checks if the different shaders have compiled successfully. */
	void compileErrors(unsigned int shader, const char* type);
};

#endif