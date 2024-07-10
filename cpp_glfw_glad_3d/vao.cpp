#include "vao.hpp"

void Vao::init(GLuint& id)
{
	glGenVertexArrays(1, &id);
}

Vao::Vao(void)
{
	init(Id);
}

void Vao::bind(void) const
{
	glBindVertexArray(Id);
}

void Vao::unbind(void)
{
	glBindVertexArray(0);
}

void Vao::config(GLuint index, GLint size, GLenum type,
	GLboolean normalized, GLsizei stride, const void* pointer) const
{
	//this->bind();
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void Vao::enable(GLint index) const
{
	glEnableVertexAttribArray(index);
}

void Vao::release(void) const
{
	glDeleteVertexArrays(1, &Id);
}
