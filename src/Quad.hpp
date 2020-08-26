#ifndef QUAD_HPP
#define QUAD_HPP

#include <GL/glew.h>
#include "vector_math.hpp"

class ShaderProgram;

class Quad {
public:
	Quad();
	~Quad();
	void setCamera(mat4 viewMatrix, mat4 camMatrix);
	void render(vec3 pos, float size, vec3 color);
private:
	ShaderProgram* shader;
	GLuint a_pos, u_view, u_cam, u_obj, u_color;
	GLuint bufVertArr, bufVert, bufInds;
};

#endif
