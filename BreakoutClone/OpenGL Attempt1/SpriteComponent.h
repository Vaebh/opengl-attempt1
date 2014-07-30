#ifndef SPRITE_COMPONENT_SIMENGINE
#define SPRITE_COMPONENT_SIMENGINE

#include "GLIncludes.h"
#include "GLUtils.h"
#include "RenderableComponent.h"
#include <string>

class SpriteComponent : public IRenderableComponent
{
public:
	SpriteComponent(const std::string inTexture = "sample.png", int inNumFrames = 1);
	~SpriteComponent();

	inline GLuint GetVAO() const {return mVao;}
	inline GLuint GetVBO() const {return mVbo;}

	virtual void Draw();
	void SetShader(const std::string inVertexShaderSrc, const std::string inFragShaderSrc);

	glm::mat4 CalculateMatrix();

	float mWidth;
	float mHeight;

	TextureData mTextureData;

	virtual void Update(float inDT);

	int mNumFrames;
	int mCurrentFrame;

	GLuint mSpriteCoord;
	GLuint mUniformSpriteIndex;

	float speed;

private:
	void Initialise();

private:
	GLuint mTexture;
	GLuint mVao;
	GLuint mVbo;

	GLint mMoveUniform;
};

#endif