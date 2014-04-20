#include "Sprite.h"
#include "Render.h"
#include "GLUtils.h"
#include <iostream>

const GLfloat vertices[] = 
{	// position					//texcoords
	-0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f,
	0.5f,  0.5f, 0.0f, 1.0f,  1.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,

	0.5f, -0.5f, 0.0f, 1.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 1.0f,  0.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f
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
	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
                     
	GLint texAttrib = glGetAttribLocation(mShader.GetProgramID(), "texcoord");
	std::cout << "TexAttrib: " << texAttrib << std::endl;
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(4*sizeof(float)));

	glUniform1i(glGetUniformLocation(mShader.GetProgramID(), "textureSprite"), 0);

	mTexture = LoadImage(inTexture.c_str());

	Render::GetSingleton()->AddEntity(static_cast<Entity*>(this));

	mMoveUniform = glGetUniformLocation(mShader.GetProgramID(), "move");
}

Sprite::~Sprite()
{

}

void Sprite::Draw()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture);

	glUseProgram(mShader.GetProgramID());

	// Calculate transformation
    glm::mat4 model;
    /*model = glm::rotate(
        model,
        90.f,
        glm::vec3(0.0f, 0.0f, 1.0f)
    );*/
	model = glm::translate(model, mPosition) * glm::scale(model, mScale);
    glUniformMatrix4fv(mMoveUniform, 1, GL_FALSE, glm::value_ptr(model));
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}