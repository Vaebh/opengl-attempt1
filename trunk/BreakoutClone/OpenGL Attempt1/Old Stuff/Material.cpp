#include "Material.h"

Material::Material(GLfloat vertices[], GLenum drawType)
{
	// Set up the vao
	glGenVertexArrays(1, &mVao);
	
	// Set up the vbo
	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, drawType);
}