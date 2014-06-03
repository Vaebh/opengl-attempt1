#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(const std::string inTexture, int inNumFrames = 1, float inAnimationSpeed = 1.f);
	virtual void Update(float inDT);
   
private:
	void SendAnimInfo();
	void ChangeFrame();
   
private:
	int mNumFrames;
	int mCurrentFrame;

	float mAnimTimer;
	GLuint mSpriteWidth;
	GLuint mUniformCurrentFrame;
};