#include "Paddle.h"

Paddle::Paddle(Ball* inBall) : Sprite("paddle.png"),
mBall(inBall)
{
	SetPosition(Vector3(0, -0.89f, 0.f));
	mScale = Vector3(0.3, 0.17, 0);
}

void Paddle::LaunchBall()
{
	mBall->mMovementEnabled = true;
}

void Paddle::Update(float inDT)
{
	Sprite::Update(inDT);

	if(!mBall->mMovementEnabled)
	{
		Vector3 ballPosition = Vector3(GetPosition().x, GetPosition().y + mScale.y*1.2f, GetPosition().z);
		mBall->SetPosition(ballPosition);
	}
}