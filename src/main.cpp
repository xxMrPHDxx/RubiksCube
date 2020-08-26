#include "Window.hpp"
#include "Quad.hpp"
#include <sstream>

void OnErrorEvent(int error_code, const char* details);
void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

static const int WIDTH = 640, HEIGHT = 480;

int main(){
	Window window(WIDTH, HEIGHT, "Rubik's Cube");
	window.setErrorCallback(OnErrorEvent);
	window.setKeyCallback(OnKeyEvent);

	mat4 camera = mat4::identity();
	mat4 view = mat4::identity();

	// Quad quad;
	// quad.setCamera(camera, view);

	// START TEST

	GLint vert, frag, program;
	GLuint a_pos = 0;

	// VERTEX SHADER
	std::stringstream ss;
	ss << "#version 300 es\n"; 
	ss << "in vec2 a_pos\n"; 
	ss << "void main(){\n";
	ss << "  gl_Position = vec4(a_pos, 1.0, 1.0);\n";
	ss << "}";
	std::string vertSrc = ss.str();
	const GLchar* vertStr = vertSrc.c_str();
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, vertSrc.size(), &vertStr, 0);
	glCompileShader(vert);
	
	// FRAGMENT SHADER
	ss.str(std::string(""));
	ss << "#version 300 es\n";
	ss << "out vec4 finalColor;\n";
	ss << "void main(){\n";
	ss << "  finalColor = vec4(1.0, 0.0, 1.0, 1.0);\n";
	ss << "}";
	std::string fragSrc = ss.str();
	const GLchar* fragStr = fragSrc.c_str();
	glShaderSource(frag, fragSrc.size(), &fragStr, 0);
	glCompileShader(frag);

	// SHADER PROGRAM
	program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);

	// BUFFERS
	GLuint vertBuf;

	// VERTEX DATA
	float vertData[2*3] = {
		-0.5, -0.5,
		 0.5, -0.5,
		 0.5,  0.5
	};
	glGenBuffers(1, &vertBuf);
	glBufferData(GL_ARRAY_BUFFER, 3*3, vertData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
	
	// END TEST

	while(window.isOpen()){
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// quad.render(vec3(0.0, 0.0, 0.0), 1.0, vec3(1.0, 0.0, 1.0));
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.pollEvents();
	}

	window.close();
	return 0;
}

void OnErrorEvent(int error_code, const char* details){
	std::cout << "Error Code " << error_code << ": " << details << std::endl;
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
