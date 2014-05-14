#ifndef SPRITE
#define SPRITE

#include "GLIncludes.h"
#include "Entity.h"
#include "Shader.h"
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

	float mWidth;
	float mHeight;

	virtual void Update(float inDT);

private:
	void Initialise();

public:
	Shader* mShader;

private:
	GLuint mTexture;
	GLuint mVao;
	GLuint mVbo;

	GLint mMoveUniform;
};

#endif