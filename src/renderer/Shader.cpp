#include "Shader.h"
#include "utilis/MessageBox.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//setup the shader binaries/programs
	const char* vertexBin = readFile(vertexFile);
	const char* fragmentBin = readFile(fragmentFile);

	//set vertex shader src and compile to machine code
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexBin, NULL);
	glCompileShader(vertexShader);
	compileStatus(mShader, ShaderType::VERTEX);

	//set fragment shader source and compile to machine code
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentBin, NULL);
	glCompileShader(fragmentShader);
	compileStatus(mShader, ShaderType::FRAGMENT);

	//create program shader and attach the vertex and fragment shader 
	mShader = glCreateProgram();
	glAttachShader(mShader, vertexShader);
	glAttachShader(mShader, fragmentShader);

	//merge them
	glLinkProgram(mShader);
	compileStatus(mShader, ShaderType::PROGRAM);

	//remove the useless shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(mShader);
}

const char* Shader::readFile(const char* fileName)
{
	std::cout << "Reading shader: " << fileName;
	std::ifstream in(fileName, std::ios::binary);

	//if file could be opened
	if (in)
	{
		//read each character and pass it inside fileContent
		std::string fileContent;
		in.seekg(0, std::ios::end);
		fileContent.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&fileContent[0], fileContent.size());
		in.close();
		printf(fileContent.empty() ? "\033[1;31m failed!\033[0m\n" : "\033[1;32m successfully!\033[0m\n");
		return fileContent.c_str();
	}
	else std::cout << "\033[1;31m failed! Path is incorrect.\033[0m\n";
	//throw("Could not read " + std::string(fileName) + ". File path is incorrect.\n");
	WinMessageBox msg(nullptr, std::string("Could not read " + std::string(fileName) + ". File path is incorrect.\n").c_str(), WinMessageBox::CRITICAL);
}

void Shader::activate()
{
	glUseProgram(mShader);
}

void Shader::Delete()
{
	glDeleteProgram(mShader);
}

void Shader::compileStatus(GLuint program, ShaderType type)
{
	int compilationStatus;
	switch (type)
	{
		//compile the program (linking errors)
	case ShaderType::PROGRAM:
		glGetProgramiv(mShader, GL_LINK_STATUS, &compilationStatus);
		if (compilationStatus == false)
		{
			GLint logLength;
			glGetProgramiv(mShader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<char> errors(logLength);
			glGetProgramInfoLog(mShader, logLength, &logLength, &errors[0]);
			std::cout << "SHADER LINKING ERRORS : \033[1;31m" << std::string(errors) << "\033[0m\n";
		}
	break;

		//compile the vertex or fragment shader (typing errors)
	case ShaderType::VERTEX:
	case ShaderType::FRAGMENT:
		glGetShaderiv(mShader, GL_COMPILE_STATUS, &compilationStatus);
		if (compilationStatus == false)
		{
			GLint logLength;
			glGetShaderiv(mShader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<char> errors(logLength);
			glGetShaderInfoLog(mShader, logLength, &logLength, &errors[0]);
			std::cout << "SHADER COMPILATION ERRORS : \033[1;31m" << std::string(errors) << "\033[0m\n";
		}
	break;
	}
}