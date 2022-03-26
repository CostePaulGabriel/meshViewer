#ifndef MESH_H 
#define MESH_H

#include "renderer/VertexArray.h"
#include "renderer/ElementBuffer.h"
#include "Texture.h"

/**@brief Some example here: https://learnopengl.com/Model-Loading/Mesh.
	A class that contains all 3d model components
 -! Note that a 3d Model has the fallowing coordinates:
 -local coordinates relative to the object origin (which can be in center but is not always the case [ex. Blender global coord, view coord., normal, etc.])
 -word coordinates origin is at the center of the world
 -view coordinates are the camera coordinates
 -screen coordinates can be viewed on the screen

 Transposing the object between these views is done by transformation matrices
  model matrix (local coord transposed to world coord)
  view matrix (world coord transposed to view coord)
  projection matrix (view coordinates transposed to clip coordinates)
  from clip coordinates (camera perspective) the transpose to screen view is done automatically
  matrices are 4d
*/

class Mesh
{
public:
	explicit Mesh(std::vector<Vertex>& vertices, std::vector<int>& indices, std::vector<Texture>& textures);
	~Mesh();

	static void loadMeshFromFile(const std::string& path);

private:
	std::string mMeshName;
	VertexArray mVertexArr;
	std::vector <Vertex> mVertices;
	std::vector <int> mIndices;
	std::vector <Texture> mTextures;
};

#endif