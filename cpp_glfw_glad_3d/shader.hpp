#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cerrno>

std::string getFileContents(const char* fileName);

class Shader {
public:
    GLuint Id;

private:
    void compileErrors(unsigned int shader, const char* type);

public:
    Shader(void);
    Shader(const char* vertexFile, const char* fragmentFile);
    void use(void) const;
    void release(void) const;
    void init(const char* vertexFile, const char* fragmentFile);
};
