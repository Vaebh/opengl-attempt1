#include "Ball.h"
#include "Render.h"
#include <iostream>

Ball::Ball(Vector3 inPosition) : Sprite("ball2.png", 2),
mVelocity(Vector3(0.f, 1.f, 0.f)),
mInitialPosition(inPosition),
mMovementEnabled(false),
mSpeed(1.6f)
{
	SetPosition(inPosition);
}

Ball::~Ball()
{

}

void Ball::OnCollision(Entity* inEntity, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox)
{
	Vector3 dirVec(0.f, -1.f, 0.f);

	if(GetPosition().x > inEntity->mBoundingBox.right)// &&
	{
		dirVec = X_UNIT_POSITIVE;
	}
	else if(GetPosition().x < inEntity->mBoundingBox.left)// &&
	{
		dirVec = X_UNIT_NEGATIVE;
	}
	else if(GetPosition().y > inEntity->mBoundingBox.top)// &&
	{
		dirVec = Y_UNIT_POSITIVE;
	}
	else if(GetPosition().y < inEntity->mBoundingBox.bottom)// &&
	{
		dirVec = Y_UNIT_NEGATIVE;
	}

	// Reflect the balls velocity based on what side of the bounding box it hits
	Vector3 velocityNorm = glm::normalize(mVelocity);
	mVelocity = (-2 * (glm::dot(velocityNorm, dirVec)) * dirVec - velocityNorm);

	// Add offset vector so bounces further from the center deflect more
	inCollisionVector *= 4;
	mVelocity += inCollisionVector;
}

void Ball::Update(float inDT)
{
	Sprite::Update(inDT);

	if(GetPosition().y <= -1.2f || glfwGetKey(Render::mWindow, GLFW_KEY_C))
	{
		mVelocity = Vector3(0.f, 0.9f, 0.f);
		mMovementEnabled = false;
		SetPosition(mInitialPosition);
	}

	if(glfwGetKey(Render::mWindow, GLFW_KEY_1))
	{
		mVelocity += Vector3(0.01f, 0.f, 0.f);
	}

	if(GetPosition().y >= 0.95f || GetPosition().y <= -0.95f || GetPosition().x >= 0.95f || GetPosition().x <= -0.95f)
	{
		if(GetPosition().y >= 0.95f)
		{
			mVelocity.y = -mVelocity.y;
		}

		if(GetPosition().y <= -0.95f)
		{

		}

		if(GetPosition().x >= 0.95f)
		{
			mVelocity.x = -mVelocity.x;
		}

		if(GetPosition().x <= -0.95f)
		{
			//flip the x
			mVelocity.x = -mVelocity.x;
		}
	}

	if(mMovementEnabled)
	{
		MovePosition(glm::normalize(mVelocity) * mSpeed * inDT);
	}
}

void Ball::Draw()
{
	Sprite::Draw();
	
	if(mAnimTimer >= 1.f)
	{
		mAnimTimer = 0.f;

		if(mCurrentFrame < mNumFrames - 1)
			mCurrentFrame += 1;
		else
			mCurrentFrame = 0;

		float spriteFrameDivisorX = 1.f / mNumFrames;

		//Vector2 spriteIndexMult(0.5f, 1.f);
		glUniform2f(mSpriteCoord, spriteFrameDivisorX, 1.f);
		glUniform1i(mUniformSpriteIndex, mCurrentFrame);
	}
}