#ifndef ANIMATED_SPRITE_COMPONENT_SIMENGINE
#define ANIMATED_SPRITE_COMPONENT_SIMENGINE

#include "SpriteComponent.h"

class AnimatedSpriteComponent : public SpriteComponent
{
public:
	AnimatedSpriteComponent(const std::string inTexture = "sample.png", int inNumFrames = 1, float inAnimationSpeed = 1.f, bool inbLooping = false);
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
	float mAnimSpeed;
	GLuint mSpriteWidth;
	GLuint mUniformCurrentFrame;

	bool mAnimating;
	bool mLooping;
};

#endif // include guard