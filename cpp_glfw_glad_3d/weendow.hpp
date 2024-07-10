#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Weendow
{
public:
	int Width;
	int Height;
	GLFWwindow* Window;
private:
	bool glfwSetWindowCenter(GLFWwindow* window);
	void init(GLFWwindow* &window, int width, int height, const char* title);

public:
	Weendow(void);
	Weendow(const char* title);
	Weendow(int squareWindowSideLength);
	Weendow(int squareWindowSideLength, const char* title);
	Weendow(int width, int height);
	Weendow(int width, int height, const char* title);
	~Weendow(void);
	bool close(void) const;
};