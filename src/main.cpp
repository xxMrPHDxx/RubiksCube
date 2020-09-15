#include "Window.hpp"
#include "Quad.hpp"
#include <cmath>

void OnErrorEvent(int error_code, const char* details);
void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

static const int WIDTH = 640, HEIGHT = 480;

void print_mat(mat4& obj){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			std::cout << obj[i*4+j];
			if(j < 3) std::cout << " ";
		}
		std::cout << "\n";
	}
	std::cout << "===============================" << std::endl;
}

int main(){
	Window window(WIDTH, HEIGHT, "Rubik's Cube");
	window.setErrorCallback(OnErrorEvent);
	window.setKeyCallback(OnKeyEvent);

	mat4 camera = mat4::lookAt(vec3(0, 0, -4), vec3(), vec3(0, 1, 0));
	mat4 view = mat4::invert(camera);
	mat4 proj = mat4::perspective(M_PI/2.0f, WIDTH*1.0f/HEIGHT, 0.01f, 100.0f);

	Quad quad;
	quad.setCamera(mat4::identity(), mat4::identity());

	while(window.isOpen()){
		glViewport(0, 0, WIDTH, HEIGHT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		quad.render(vec3(0.0, 0.0, -1.0), 1.0, vec3(1.0, 0.0, 1.0));

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
