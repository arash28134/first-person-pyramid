#pragma once

#include <GL/glew.h>

class Mesh
{
public:
	Mesh();

	// creating a mesh, based on the given array of vertices and indices and number of vertices and indices
	void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);

	// rendering a mesh
	void RenderMesh();
	~Mesh();
private:
	GLuint VAO, VBO, IBO, indexCount;
};