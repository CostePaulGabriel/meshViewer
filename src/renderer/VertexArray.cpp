#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mVertexArray);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::linkVertexArray(VertexBuffer& vertexBuff, int layout, int totalVertBuff, int type, GLsizeiptr stride, void* offset, bool normalized)
{
	vertexBuff.bind();
	glVertexAttribPointer(layout, totalVertBuff, type, normalized, stride, offset);
	glEnableVertexAttribArray(layout);
	vertexBuff.unbind();
}

void VertexArray::bind()
{
	glBindVertexArray(mVertexArray);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::deleteVertexArray()
{
	glDeleteVertexArrays(1, &mVertexArray);
}