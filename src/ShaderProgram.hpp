#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL/glew.h>

class ShaderProgram {
public:
	ShaderProgram(const char* vertSrc, const char* fragSrc);
	~ShaderProgram();
	void bind();
	GLint getAttribLocation(const char* name);
	GLint getUniformLocation(const char* name);
	void bindFragDataLocation(const int pos, const char* name);
private:
	GLint program;
	static GLint createShader(const char* source, GLenum type);
	static GLint createProgram(GLint vert, GLint frag);
};

#endif
