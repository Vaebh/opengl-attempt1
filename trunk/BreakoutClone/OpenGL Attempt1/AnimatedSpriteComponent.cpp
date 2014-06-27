#include "AnimatedSpriteComponent.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(const std::string inTexture, int inNumFrames, float inAnimationSpeed, bool inbLooping) : SpriteComponent(inTexture),
mAnimSpeed(inAnimationSpeed),
mNumFrames(inNumFrames),
mCurrentFrame(0),
mAnimating(true),
mLooping(inbLooping)
{
    SendAnimInfo();
}

void AnimatedSpriteComponent::Play(bool inbLooping)
{
    mbLooping = inbLooping;
    mbAnimating = true;
}

void AnimatedSpriteComponent::Stop()
{
    mbAnimating = false;
}
 
void AnimatedSpriteComponent::ChangeFrame()
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
 
void AnimatedSpriteComponent::SendAnimInfo()
{
    float spriteFrameDivisorX = 1.f / mNumFrames;
      
    glUniform2f(mSpriteWidth, spriteFrameDivisorX, 1.f);
    glUniform1i(mUniformCurrentFrame, mCurrentFrame);
}
 
void AnimatedSpriteComponent::Update(float inDT)
{
  SpriteComponent::Update(inDT);

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