#include "SpriteComponent.h"

#include "RenderSystem.h"
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

const std::string DEFAULT_VERT_SHADER = "2DVertexShaderMove.txt";
const std::string DEFAULT_FRAG_SHADER = "2DFragShaderPlain.txt";

using namespace std;

SpriteComponent::SpriteComponent(const std::string inTexture, int inNumFrames) :
IRenderableComponent(),
mNumFrames(inNumFrames),
mCurrentFrame(0),
mColourTintUniform(0),
mColourTint(Vector4(0.f, 0.f, 0.f, 1.f))
{
	Initialise();
	SetShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);

	mTextureData = LoadImage(inTexture.c_str());
}

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::Initialise()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);

	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void SpriteComponent::SetShader(const std::string inVertexShaderSrc, const std::string inFragShaderSrc)
{
	if(inVertexShaderSrc.empty() || inFragShaderSrc.empty())
		return;

	if(mShader != NULL)
		delete mShader;

	mShader = new Shader(inVertexShaderSrc, inFragShaderSrc);

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
	mSpriteCoord = glGetUniformLocation(mShader->GetProgramID(), "spriteOffset");
	mUniformSpriteIndex = glGetUniformLocation(mShader->GetProgramID(), "currentFrame");
	mColourTintUniform = glGetUniformLocation(mShader->GetProgramID(), "uniformColour");


	// TODO - REMOVE ALL STATEMENTS BELOW THIS WHEN THIS HAS BEEN TESTED

	//glUniform2f(mSpriteCoord, 1.f, 1.f);
	//glUniform1i(mUniformSpriteIndex, 0);

	float spriteFrameDivisorX = 1.f / mNumFrames;

	//Vector2 spriteIndexMult(0.5f, 1.f);
	glUniform2f(mSpriteCoord, spriteFrameDivisorX, 1.f);
	glUniform1i(mUniformSpriteIndex, mCurrentFrame);
}

glm::mat4 SpriteComponent::CalculateMatrix()
{
	glm::mat4 model;
	model = glm::translate(model, GetOwner()->GetPosition()) * glm::scale(model, GetOwner()->mScale) * glm::rotate(model, GetOwner()->mRotationAngle.x, X_UNIT_POSITIVE) * glm::rotate(model, GetOwner()->mRotationAngle.y, Y_UNIT_POSITIVE) * glm::rotate(model, GetOwner()->mRotationAngle.z, Z_UNIT_POSITIVE);

	return model;
}

void SpriteComponent::Update(float inDT)
{
	//mAnimTimer += inDT;
	//IRenderableComponent::Update(inDT);
}

void SpriteComponent::Draw()
{
	//glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureData.textureID);

	//glUseProgram(mShader->GetProgramID());

	// Calculate transformation
    glUniformMatrix4fv(mMoveUniform, 1, GL_FALSE, glm::value_ptr(CalculateMatrix()));

    float spriteFrameDivisorX = 1.f / mNumFrames;

	//Vector2 spriteIndexMult(0.5f, 1.f);
	glUniform2f(mSpriteCoord, spriteFrameDivisorX, 1.f);
	glUniform1i(mUniformSpriteIndex, mCurrentFrame);

	glUniform4f(mColourTintUniform, mColourTint.x, mColourTint.y, mColourTint.z, mColourTint.w);
}