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

const std::string defaultVertexShader = "2DVertexShaderMove.txt";
const std::string defaultFragShader = "2DFragShaderPlain.txt";

using namespace std;

Sprite::Sprite(const std::string inTexture) : Entity()
{
	Initialise();
	SetShader(defaultVertexShader, defaultFragShader);

	mTextureData = LoadImage(inTexture.c_str());
}

Sprite::~Sprite()
{

}

void Sprite::Initialise()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Sprite::SetShader(const std::string inVertexShaderSrc, const std::string inFragShaderSrc)
{
	if(inVertexShaderSrc.empty() || inFragShaderSrc.empty())
		return;

	if(mShader)
		delete mShader;

	mShader = new Shader(inVertexShaderSrc, inFragShaderSrc);

	if(glIsProgram(mShader->mShaderProgram) == GL_TRUE)
		cout << "sprite isProgram success" << endl;
	else
		cout << "sprite isProgram fail" << endl;

	glUseProgram(mShader->mShaderProgram);

	glBindVertexArray(mVao);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);

	GLint posAttrib = glGetAttribLocation(mShader->GetProgramID(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
                     
	GLint texAttrib = glGetAttribLocation(mShader->GetProgramID(), "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(4*sizeof(float)));

	glUniform1i(glGetUniformLocation(mShader->GetProgramID(), "textureSprite"), 0);

	mMoveUniform = glGetUniformLocation(mShader->GetProgramID(), "move");
}

glm::mat4 Sprite::CalculateMatrix()
{
	glm::mat4 model;
	model = glm::translate(model, mPosition) * glm::scale(model, mScale) * glm::rotate(model, mRotationAngle.x, X_UNIT_POSITIVE) * glm::rotate(model, mRotationAngle.y, Y_UNIT_POSITIVE) * glm::rotate(model, mRotationAngle.z, Z_UNIT_POSITIVE);
    glUniformMatrix4fv(mMoveUniform, 1, GL_FALSE, glm::value_ptr(model));

	return model;
}

void Sprite::Update(float inDT)
{
	Entity::Update(inDT);
}

void Sprite::Draw()
{
	//glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureData.textureID);

	//glUseProgram(mShader->GetProgramID());

	// Calculate transformation
    glm::mat4 model;
	model = glm::translate(model, mPosition) * glm::scale(model, mScale) * glm::rotate(model, mRotationAngle.x, X_UNIT_POSITIVE) * glm::rotate(model, mRotationAngle.y, Y_UNIT_POSITIVE) * glm::rotate(model, mRotationAngle.z, Z_UNIT_POSITIVE);
    glUniformMatrix4fv(mMoveUniform, 1, GL_FALSE, glm::value_ptr(model));
	
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}