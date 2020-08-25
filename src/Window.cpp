#include "Window.hpp"

void Window::setErrorCallback(GLFWerrorfun fun){
	glfwSetErrorCallback(fun);
}

void Window::setKeyCallback(GLFWkeyfun fun){
	if(window) glfwSetKeyCallback(window, fun);
}

void Window::pollEvents(){
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::close(){
	glfwSetWindowShouldClose(window, GLFW_TRUE);
	glfwDestroyWindow(window);
	glfwTerminate();
}

/*****************************************/
/*           PRIVATE METHODS             */
/*****************************************/

void Window::initContext(){
	if(!glfwInit())
		throw std::invalid_argument("Failed to initialize GLFW!");
	this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if(!window){
		glfwTerminate();
		throw std::invalid_argument("Failed to create window!");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	glfwMakeContextCurrent(window);
	
	if(glewInit() != GLEW_OK){
		close();
		throw std::invalid_argument("Failed to initialize GLEW!");
	}else if(!GLEW_VERSION_2_1)
		throw std::invalid_argument("This machine doesn't support OpenGL 2.1");
	
	glfwShowWindow(window);
}
