#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const std::string inTexture, int inNumFrames, float inAnimationSpeed) : Sprite(inTexture),
mAnimSpeed(inAnimationSpeed),
mNumFrames(inNumFrames),
mCurrentFrame(0)
{
    SendAnimInfo();
}
 
void AnimatedSprite::ChangeFrame()
{
    if(mCurrentFrame < mNumFrames - 1)
      mCurrentFrame += 1;
    else
      mCurrentFrame = 0;

      SendAnimInfo();
}
 
void AnimatedSprite::SendAnimInfo()
{
      float spriteFrameDivisorX = 1.f / mNumFrames;
      
      glUniform2f(mSpriteWidth, spriteFrameDivisorX, 1.f);
      glUniform1i(mUniformCurrentFrame, mCurrentFrame);
}
 
void AnimatedSprite::Update(float inDT)
{
    mAnimTimer += inDT;
    
    if(mAnimTimer >= mAnimSpeed)
    {
      mAnimTimer = 0;
      ChangeFrame();
    }
}