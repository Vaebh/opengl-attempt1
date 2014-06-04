#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const std::string inTexture, int inNumFrames, float inAnimationSpeed, bool inbLooping) : Sprite(inTexture),
mAnimSpeed(inAnimationSpeed),
mNumFrames(inNumFrames),
mCurrentFrame(0),
mAnimating(true),
mLooping(inbLooping)
{
    SendAnimInfo();
}

void AnimatedSprite::Play(bool inbLooping)
{
    mbLooping = inbLooping;
    mbAnimating = true;
}

void AnimatedSprite::Stop()
{
    mbAnimating = false;
}
 
void AnimatedSprite::ChangeFrame()
{
    if(mCurrentFrame < mNumFrames - 1)
      mCurrentFrame += 1;
    else
    {
      mCurrentFrame = 0;
      
      if(!mLooping)
      {
          Stop();
      }
    }

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
  if(mAnimating)
  {
      mAnimTimer += inDT;
      
      if(mAnimTimer >= mAnimSpeed)
      {
          mAnimTimer = 0;
          ChangeFrame();
      }
  }
}