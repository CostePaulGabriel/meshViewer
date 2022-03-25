#ifndef TEXTURE_H
#define TEXTURE_H

#include "renderer/Shader.h"
#include <stb/stb_image.h>
//#include <GLFW/glfw3.h>

/**
* @brief Texture class will represent an image in pixel coordinates that can be mapped onto a 3D model.
*/

enum class TextureType{ DIFFUSE, SPECULAR, NORMAL };

class Texture
{
public:
	Texture(const char* image, const char* texType, GLuint slot);
	~Texture();

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	void bind();
	void unbind();
	void deleteTexture();
	
	GLuint getId() { return mId; }
	GLuint getUnit() { return mUnit; }
	const char* getType() { return mType; }

private:
	GLuint mId;
	GLuint mUnit;
	const char* mType; //TextureType m_type;
};

#endif