#include "Ball.h"

Ball::Ball() : Sprite("ball.png"), mSpeed(0.0002f)
{
	
}

void Ball::OnCollision()
{
	mSpeed = -mSpeed;
}

void Ball::Update(float inDT)
{
	Sprite::Update(inDT);

	if(GetPosition().y <= -0.95 || GetPosition().y >= 0.95)
	{
		mSpeed = -mSpeed;
	}

	MovePosition(Vector3(0, mSpeed, 0) * Y_UNIT_NEGATIVE);
}