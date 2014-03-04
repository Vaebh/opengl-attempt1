#include "Sprite.h"
#include <iostream>

const GLfloat vertices[] = 
{
	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f,  1.0f,  1.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f
};

const unsigned int kNumVertsForSprites = 4;

Sprite::Sprite(const std::string inTexture, const std::string inVertexShaderSrc, const std::string inFragShaderSrc) : Entity()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	mShader = Shader(inVertexShaderSrc, inFragShaderSrc);

	glUseProgram(mShader.GetProgramID());

	GLint posAttrib = glGetAttribLocation(mShader.GetProgramID(), "position");
	std::cout << "PositionAttrib: " << posAttrib << std::endl;
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
                     
	GLint texAttrib = glGetAttribLocation(mShader.GetProgramID(), "texcoord");
	std::cout << "TexAttrib: " << texAttrib << std::endl;
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
}