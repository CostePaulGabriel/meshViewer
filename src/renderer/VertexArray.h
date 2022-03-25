#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "renderer/VertexBuffer.h"

/*@brief:
	A "vertex array object" has multiple "vertex buffer object" components, each vertex stores data such as coordinates, UV, 
	texture, normal(tangent to the point location). 
	To link the vertex buffer objects to the vertex array object I call the linkVertexArray function.
	The vertex array object data are stored by the CPU in the RAM memory and will be loaded in the GPU VRAM by calling the "bind()" function.
*/

class VertexArray
{
public:
	explicit VertexArray();
	~VertexArray();

	/*@brief: A function that links the VertexBufferObject to the VertexArray.
	* More details here: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml.
	* @params: vertexBuff - the linked buffer
	* @params: layout - an index of the current vertex array
	* @params: vboCount - number of vertex buffers
	* @params: type - the type of the array components
	* @params: stride - byte offset between consecutive generic vertex attributes
	* @params: offset - Specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target, default is 0
	* @params: normalized - specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) 
	*/
	void linkVertexArray(VertexBuffer& vertexBuff, int layout, int vboCount, int type, GLsizeiptr stride, void* offset, bool normalized = false);
	
	void bind();
	void unbind();
	void deleteVertexArray();

	GLuint getVertexArray() { return mVertexArray; }
private:
	GLuint mVertexArray;
};

#endif