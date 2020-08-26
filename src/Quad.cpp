#include "Quad.hpp"
#include "utils.hpp"
#include "ShaderProgram.hpp"

Quad::Quad(){
	std::string vertSrc = loadTextFile("data/quad_vert.glsl");
	std::string fragSrc = loadTextFile("data/quad_frag.glsl");
	this->shader = new ShaderProgram(vertSrc.c_str(), fragSrc.c_str());

	shader->bind();

	this->a_pos   = shader->getAttribLocation("a_pos");
	this->u_view  = shader->getUniformLocation("u_view");
	this->u_cam   = shader->getUniformLocation("u_cam");
	this->u_obj   = shader->getUniformLocation("u_obj");
	this->u_color = shader->getUniformLocation("u_color");

	float vertData[4*3] = {
		-0.5, -0.5, 0.0,
		 0.5, -0.5, 0.0,
		 0.5,  0.5, 0.0,
		-0.5,  0.5, 0.0,
	};
	float indsData[6] = { 0, 1, 2, 0, 2, 3 };

	glGenVertexArrays(1, &bufVertArr);
	glBindVertexArray(bufVertArr);
	glGenBuffers(1, &bufVert);
	glBindBuffer(GL_ARRAY_BUFFER, bufVert);
	glBufferData(GL_ARRAY_BUFFER, 4*3, vertData, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &bufInds);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufInds);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6, indsData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Quad::~Quad(){
	delete this->shader;
}

void Quad::setCamera(mat4 viewMatrix, mat4 camMatrix){
	this->shader->bind();
	glUniformMatrix4fv(u_view, 16, false, viewMatrix.data);
	glUniformMatrix4fv(u_cam, 16, false, camMatrix.data);
}

void Quad::render(vec3 pos, float size, vec3 color){
	this->shader->bind();
	
	mat4 objMatrix = mat4::identity();
	glUniformMatrix4fv(u_obj, 16, false, objMatrix.data);
	glUniform4f(u_color, color.x, color.y, color.z, 1.0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) NULL);
}
