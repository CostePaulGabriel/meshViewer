#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "widgets/AbstractWidgets.h"

// https://en.wikipedia.org/wiki/Vertex_buffer_object , https://www.khronos.org/opengl/wiki/Vertex_Specification

/*@brief:
	A vertex buffer object is a list of vertices that will be linked with the vertex array object to create an OpenGl drawing call.
	A vertex buffer should store vertex coordinates, color, UVtexture, normal(tangent on that point) 
*/

class Vertex
{
	glm::vec3 coordinates;
	glm::vec2 UVtexture;
	glm::vec3 color;
	glm::vec3 normal;
};

class VertexBuffer
{
public:
	explicit VertexBuffer(std::vector<Vertex>& vertices);
	virtual ~VertexBuffer();

	void bind();
	void unbind();
	void deleteVertexBuffer();

	GLuint getVertexBuffer() { return mVertexBuffer; }
private:
	GLuint mVertexBuffer;	//index of VBO
};

#endif