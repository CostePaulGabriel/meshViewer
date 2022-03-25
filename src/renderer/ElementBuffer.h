#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

#include "widgets/AbstractWidgets.h"
#include <vector>

/* More about indexing vertex buffers here: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-9-vbo-indexing/.
* @brief:
* Since now, I used the vertex buffer to generate vertices without checking if the vertices were duplicated when they form a triangle.
* To solve this problem I created the ElementBuffer class which will filter the vertices in a way that there will never exist duplicates.
* This process is done by indexing the VertexBufferObject.
*/

class ElementBuffer
{
public:
	explicit ElementBuffer(std::vector<int>& indices);
	~ElementBuffer();

	void bind();
	void unbind();
	void deleteElemBuffer();

	GLuint getElemBuffer() { return mElemBuffer; }
private:
	GLuint mElemBuffer;
};

#endif