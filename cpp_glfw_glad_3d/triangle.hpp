#pragma once

#include <glad/glad.h>
#include <vector>
#include "vao.hpp"
#include "vbo.hpp"
#include "ebo.hpp"
#include "shader.hpp"

class Triangle {
public:
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	Vao vao;
	Vbo vbo;
	Ebo ebo;
	Shader shader;

public:
	Triangle(void);
	~Triangle(void);
	void use(void) const;
};