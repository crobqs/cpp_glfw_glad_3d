#include "weendow.hpp"
#include "triangle.hpp"

int main(void) {
	Weendow w;

	std::vector<GLfloat> vertices = {
		/* x	y	z	r	g	b */
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.2f, 1.0f, 0.5f,
		 0.5f, -0.5f, 0.0f, 0.5f, 0.2f, 1.0f
	};
	std::vector<GLuint> indices = {
		/* a	b	c */
		0, 1, 2
	};
	Shader shader("default.vert", "default.frag");
	Vao vao;
	Vbo vbo;
	Ebo ebo;
	vao.bind();
	vbo.bind();
	ebo.bind();
	vbo.config(vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	ebo.config(indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	vao.config(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(0));
	vao.config(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(3 * sizeof(GLfloat)));
	vao.enable(0);
	vao.enable(1);
	vao.unbind();
	vbo.unbind();
	ebo.unbind();


	while (!w.close()) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.use();
		vao.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(w.Window);
	}

	vao.release();
	vbo.release();
	ebo.release();
	shader.release();
	
	return 0;
}