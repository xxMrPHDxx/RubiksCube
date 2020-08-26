#include "ShaderProgram.hpp"
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

ShaderProgram::ShaderProgram(const char* vertSrc, const char* fragSrc){
	GLint vert = ShaderProgram::createShader(vertSrc, GL_VERTEX_SHADER);
	GLint frag = ShaderProgram::createShader(fragSrc, GL_FRAGMENT_SHADER);
	this->program = ShaderProgram::createProgram(vert, frag);
}

void ShaderProgram::bind(){
	glUseProgram(this->program);
}

GLint ShaderProgram::getAttribLocation(const char* name){
	return glGetAttribLocation(this->program, name);
}

GLint ShaderProgram::getUniformLocation(const char* name){
	return glGetUniformLocation(this->program, name);
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
		std::stringstream ss;
		ss << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
		ss << " SHADER: " << log; 
		throw std::invalid_argument(ss.str().c_str());
	}
	return shader;
}

GLint ShaderProgram::createProgram(GLint vert, GLint frag){
	GLint program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);
	glDeleteShader(vert);
	glDeleteShader(frag);

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
