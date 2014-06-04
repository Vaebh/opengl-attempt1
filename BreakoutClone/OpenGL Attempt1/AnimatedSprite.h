#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(const std::string inTexture, int inNumFrames = 1, float inAnimationSpeed = 1.f, bool inbLooping = false);
	virtual void Update(float inDT);

	void Play(bool inbLooping);
	void Stop();
	bool IsAnimating() const {return mAnimating;}
   
private:
	void SendAnimInfo();
	void ChangeFrame();
   
private:
	int mNumFrames;
	int mCurrentFrame;

	float mAnimTimer;
	GLuint mSpriteWidth;
	GLuint mUniformCurrentFrame;

	bool mAnimating;
	bool mLooping;
};