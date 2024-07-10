#include "shader.hpp"

Shader::Shader(void)
{
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	init(vertexFile, fragmentFile);
}

void Shader::init(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	Id = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(Id, vertexShader);
	glAttachShader(Id, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(Id);
	// Checks if Shaders linked succesfully
	compileErrors(Id, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use(void) const
{
	glUseProgram(this->Id);
}

void Shader::release(void) const
{
	glDeleteProgram(this->Id);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

std::string getFileContents(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw(errno);
}