#ifndef SPRITE
#define SPRITE

#include "GLIncludes.h"
#include "GLUtils.h"
#include "Entity.h"
#include <string>

class Sprite : public Entity
{
public:
	Sprite(const std::string inTexture = "sample.png");
	~Sprite();

	inline GLuint GetVAO() const {return mVao;}
	inline GLuint GetVBO() const {return mVbo;}

	virtual void Draw();
	void SetShader(const std::string inVertexShaderSrc, const std::string inFragShaderSrc);

	glm::mat4 CalculateMatrix();

	float mWidth;
	float mHeight;

	TextureData mTextureData;

	virtual void Update(float inDT);

private:
	void Initialise();

private:
	GLuint mTexture;
	GLuint mVao;
	GLuint mVbo;

	GLint mMoveUniform;
};

#endif