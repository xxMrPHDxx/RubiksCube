#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, std::string title) :
		width(width),
		height(height),
		title(title) {
		initContext();
	}
	const int& getWidth() const { return this->width; }
	const int& getHeight() const { return this->height; }
	const bool isOpen() const { 
		if(!window) return false;
		return !glfwWindowShouldClose(window);
	}
	void setErrorCallback(GLFWerrorfun);
	void setKeyCallback(GLFWkeyfun);
	void pollEvents();
	void close();
private:
	GLFWwindow *window;
	int width, height;
	std::string title;
	void initContext();
};

#endif
