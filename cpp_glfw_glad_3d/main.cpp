#include "weendow.hpp"
#include "triangle.hpp"

int main(void) {
	Weendow w;
	Triangle triangle;

	while (!w.close()) {
		glfwPollEvents();
		triangle.use();
		glfwSwapBuffers(w.Window);
	}

	return 0;
}