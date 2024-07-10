#include "vbo.hpp"

void Vbo::init(GLuint& id)
{
	glGenBuffers(1, &id);
}

Vbo::Vbo(void)
{
	init(Id);
}

void Vbo::bind(void) const
{
	glBindBuffer(GL_ARRAY_BUFFER, Id);
}

void Vbo::unbind(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vbo::config(GLsizeiptr size, const void* data, GLenum usage) const
{
	//this->bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void Vbo::release(void) const
{
	glDeleteBuffers(1, &Id);
}
