#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(std::vector<int>& indices)
{
	glGenBuffers(1, &mElemBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElemBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &mElemBuffer);
}

void ElementBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElemBuffer);
}

void ElementBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::deleteElemBuffer()
{
	glDeleteBuffers(1, &mElemBuffer);
}