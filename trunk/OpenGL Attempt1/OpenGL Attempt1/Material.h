#ifndef MATERIAL_SIMENGINE
#define MATERIAL_SIMENGINE

#include "GLUtils.h"
#include "Shader.h"

class Material
{
public:
	Material(GLfloat vertices[], GLenum drawType = GL_STATIC_DRAW);
	~Material();

	inline GLuint GetVAO() const {return mVao;}
	inline GLuint GetVBO() const {return mVbo;}

private:
	GLuint mVao;
	GLuint mVbo;

	Shader mShader;
};

#endif