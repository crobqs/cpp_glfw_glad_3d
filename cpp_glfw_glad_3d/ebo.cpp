#include "ebo.hpp"

void Ebo::init(GLuint& id)
{
	glGenBuffers(1, &id);
}

Ebo::Ebo(void)
{
	init(Id);
}

void Ebo::bind(void) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
}

void Ebo::unbind(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Ebo::config(GLsizeiptr size, const void* data, GLenum usage) const
{
	//this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void Ebo::release(void) const
{
	glDeleteBuffers(1, &(this->Id));
}
