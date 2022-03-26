#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const char* image, const char* textureType, GLuint slot)
{
	// Assigns the type of the texture ot the texture object
	mType = textureType;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, colorChannels;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &colorChannels, 0);

	// Generates an OpenGL texture object
	glGenTextures(1, &mId);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	mUnit = slot;
	glBindTexture(GL_TEXTURE_2D, mId);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Check what type of color channels the texture has and load it accordingly
	if (colorChannels == 4)
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,widthImg,heightImg,0,GL_RGBA,GL_UNSIGNED_BYTE,bytes);
	else if (colorChannels == 3)
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,widthImg,heightImg,0,GL_RGB,GL_UNSIGNED_BYTE,bytes);
	else if (colorChannels == 1)
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,widthImg,heightImg,0,GL_RED,GL_UNSIGNED_BYTE,bytes);
	else
		throw std::invalid_argument("Automatic Texture type recognition failed");

	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mId);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.get(), uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.activate();
	// Sets the value of the uniform
	glUniform1i(texUni, mUnit);
}

bool Texture::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
// Load from file
int image_width = 0;
int image_height = 0;
unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
if (image_data == NULL)
return false;

// Create a OpenGL texture identifier
GLuint image_texture;
glGenTextures(1, &image_texture);
glBindTexture(GL_TEXTURE_2D, image_texture);

// Setup filtering parameters for display
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
stbi_image_free(image_data);

*out_texture = image_texture;
*out_width = image_width;
*out_height = image_height;

return true;
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + mUnit);
	glBindTexture(GL_TEXTURE_2D, mId);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::deleteTexture()
{
	glDeleteTextures(1, &mId);
}
