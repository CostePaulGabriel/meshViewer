#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cerrno> //for error debugging
#include <vector>

#include "widgets/AbstractWidgets.h"

/**@brief:
	Shaders are OpenGl programs that allow the GPU to perform tasks such as: colors, shading, lighting, special effects.
	Shader class will read, activate or deactivate an OpenGl shader program written in openGl shading language(glsl), 
	note that Shader programs run only on GPU.
	There are two important shaders located in this program "shaders" folder: "vertex shader" and "fragment shader".
		The "vertex shader" will take as input a vertex attribute, known as vertex array, loads the attribute in the glsl program, compile it and outputs 
	the verticies on the screen. Note that this shader runs once per vertex.
		The "fragment shader" will load a texture, compile it, and outputs the graphic primitives pixels color on the screen. 
	Note that this shader runs once per rendered pixel.
*/

enum class ShaderType : int {PROGRAM, VERTEX, FRAGMENT};

class Shader 
{
public:
	explicit Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();
	
	/**@brief: Read shader program from a file.*/
	const char* readFile(const char* fileName);
	/**@brief: Make current shader active. */
	void activate();
	/**@brief: Delete the current shader. */
	void Delete();
	/**@brief: Debugger tool for shader code.*/
	void compileStatus(GLuint program, ShaderType type = ShaderType::VERTEX);

	GLuint get() { return mShader; }
private:
	GLuint mShader;
};

#endif // !SHADER_H