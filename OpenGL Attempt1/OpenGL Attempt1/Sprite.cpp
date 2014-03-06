#include "Sprite.h"
#include "Render.h"
#include "GLUtils.h"
#include <iostream>

const GLfloat vertices[] = 
{
	-0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  1.0f, 1.0f,

	0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.0f, 0.0f
};

const unsigned int kNumVertsForSprites = 4;

using namespace std;

Sprite::Sprite(const std::string inTexture, const std::string inVertexShaderSrc, const std::string inFragShaderSrc) : Entity()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Shader aShader = Shader(inVertexShaderSrc, inFragShaderSrc);
	mShader = aShader;

	if(glIsProgram(mShader.mShaderProgram) == GL_TRUE)
		cout << "sprite isProgram success" << endl;
	else
		cout << "sprite isProgram fail" << endl;

	glUseProgram(mShader.mShaderProgram);
	cout << "shaderID:" << mShader.GetProgramID() << endl;

	glBindVertexArray(mVao);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);

	//Setup2D(mShader.GetProgramID());

	GLint posAttrib = glGetAttribLocation(mShader.GetProgramID(), "position");
	std::cout << "PositionAttrib: " << posAttrib << std::endl;
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
                     
	GLint texAttrib = glGetAttribLocation(mShader.GetProgramID(), "texcoord");
	std::cout << "TexAttrib: " << texAttrib << std::endl;
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));

	glUniform1i(glGetUniformLocation(mShader.GetProgramID(), "textureSprite"), 0);

	mTexture = LoadImage(inTexture.c_str());

	Render::GetSingleton()->AddEntity(static_cast<Entity*>(this));
}

Sprite::~Sprite()
{

}

void Sprite::Draw()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture);

	glUseProgram(mShader.GetProgramID());
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}