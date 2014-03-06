#include "GLIncludes.h"
#include "Entity.h"
#include "Shader.h"
#include <string>

class Sprite : public Entity
{
public:
	Sprite(const std::string inTexture = "sample.png", const std::string inVertexShaderSrc = "2DVertexShader.txt", const std::string inFragShaderSrc = "2DFragShader.txt");
	~Sprite();

	inline GLuint GetVAO() const {return mVao;}
	inline GLuint GetVBO() const {return mVbo;}

	virtual void Draw();

public:

	Shader mShader;

private:
	
	GLuint mTexture;
	GLuint mVao;
	GLuint mVbo;
};