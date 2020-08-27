#include "Quad.hpp"
#include "utils.hpp"
#include "ShaderProgram.hpp"

Quad::Quad(){
	std::string vertSrc = loadTextFile("data/quad_vert.glsl");
	std::string fragSrc = loadTextFile("data/quad_frag.glsl");
	this->shader = new ShaderProgram(vertSrc.c_str(), fragSrc.c_str());

	GLfloat vertData[4*3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	GLushort indsData[6] = { 0, 1, 2, 0, 2, 3 };

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indsData), indsData, GL_STATIC_DRAW);

	a_pos   = shader->getAttribLocation("a_pos");
	u_view  = shader->getUniformLocation("u_view");
	u_cam   = shader->getUniformLocation("u_cam");
	u_obj   = shader->getUniformLocation("u_obj");
	u_color = shader->getUniformLocation("u_color");
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

	mat4 objMatrix = mat4::identity()
		.translate(pos.x+0.5f, pos.y+0.5f, pos.z+0.5f)
		.scale(size*0.99f, size*0.99f, size*0.99f);

	glUniformMatrix4fv(u_obj, 16, false, objMatrix.data);
	glUniform4f(u_color, color.x, color.y, color.z, 1.0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(a_pos);
	glVertexAttribPointer(a_pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
