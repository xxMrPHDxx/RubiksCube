#include "ShaderProgram.hpp"
#include <iostream>
#include <cstring>
#include <vector>

ShaderProgram::ShaderProgram(const char* vertSrc, const char* fragSrc){
	GLint vert = ShaderProgram::createShader(vertSrc, GL_VERTEX_SHADER);
	GLint frag = ShaderProgram::createShader(fragSrc, GL_FRAGMENT_SHADER);
	this->program = ShaderProgram::createProgram(vert, frag);
}

/************************************************/
/*               STATIC METHODS                 */
/************************************************/

GLint ShaderProgram::createShader(const char* source, GLenum type){
	GLint shader = glCreateShader(type);
	GLint len = strlen(source);
	glShaderSource(shader, 1, &source, &len);
	glCompileShader(shader);
	
	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(compiled == GL_FALSE){
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
		std::string log(begin(errorLog), end(errorLog));
		throw std::invalid_argument(log.c_str());
	}
	return shader;
}

GLint ShaderProgram::createProgram(GLint vert, GLint frag){
	GLint program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glDeleteShader(vert);
	glDeleteShader(frag);
	glLinkProgram(program);

	GLint linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(linked == GL_FALSE){
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);
		std::string log(begin(errorLog), end(errorLog));
		throw std::invalid_argument(log.c_str());
	}
	return program;
}
