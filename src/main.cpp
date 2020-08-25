#include "Window.hpp"

void OnErrorEvent(int error_code, const char* details);
void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

static const int WIDTH = 640, HEIGHT = 480;

int main(){
	Window window(WIDTH, HEIGHT, "Rubik's Cube");
	window.setErrorCallback(OnErrorEvent);
	window.setKeyCallback(OnKeyEvent);

	while(window.isOpen()){
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

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
