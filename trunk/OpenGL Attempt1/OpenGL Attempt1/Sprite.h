#include "GLIncludes.h"
#include "Entity.h"
#include "Shader.h"
#include <string>

class Sprite : public Entity
{
public:
	Sprite(const std::string inTexture, const std::string inVertexShaderSrc = "2DVertexShader.txt", const std::string inFragShaderSrc = "2DFragShader.txt");
	~Sprite();

	inline GLuint GetVAO() const {return mVao;}
	inline GLuint GetVBO() const {return mVbo;}

	virtual void Draw();

private:
	Shader mShader;

	GLuint mVao;
	GLuint mVbo;
};