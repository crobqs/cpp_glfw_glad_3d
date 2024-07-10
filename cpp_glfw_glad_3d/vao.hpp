#pragma once

#include <glad/glad.h>

class Vao {
public:
	GLuint Id;

private:
	void init(GLuint &id);

public:
	Vao(void);
	void bind(void) const;
	void unbind(void);
	void config(GLuint index, GLint size, GLenum type,
		GLboolean normalized, GLsizei stride, const void* pointer) const;
	void enable(GLint index) const;
	void release(void) const;
};