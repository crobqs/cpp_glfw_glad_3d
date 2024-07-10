#pragma once

#include <glad/glad.h>

class Ebo {
public:
	GLuint Id;
private:
	void init(GLuint& id);
public:
	Ebo(void);
	void bind(void) const;
	void unbind(void);
	void config(GLsizeiptr size, const void* data, GLenum usage) const;
	void release(void) const;
};