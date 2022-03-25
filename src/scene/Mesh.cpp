#include "Mesh.h"
#if 0
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<int>& indices, std::vector<Texture>& textures)
{

	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	vertexArr.bind();
	// Generates Vertex Buffer Object and links it to vertices
	VertexBuffer vertexBuff(vertices);
	// Generates Element Buffer Object and links it to indices
	ElementBuffer elemBuff(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	vertexArr.linkVertexArray(vertexBuff, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vertexArr.linkVertexArray(vertexBuff, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vertexArr.linkVertexArray(vertexBuff, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vertexArr.linkVertexArray(vertexBuff, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	vertexArr.unbind();
	vertexBuff.unbind();
	elemBuff.unbind();
}

Mesh::~Mesh()
{
}
#endif
