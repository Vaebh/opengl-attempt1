#include "Ball.h"
#include "Render.h"
#include <iostream>

Ball::Ball(Vector3 inPosition) : Sprite("ball.png"),
mVelocity(Vector3(0.f, 1.f, 0.f)),
mInitialPosition(inPosition),
mMovementEnabled(false),
mSpeed(0.9f)
{
	SetPosition(inPosition);
}

Ball::~Ball()
{

}

void Ball::OnCollision(Entity* inEntity, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox)
{
	//mVelocity = -mVelocity;
	Vector3 dirVec(-1.f, -1.f, 0.f);

	// Checks which side of the colliding entity the ball is on, then sets the direction
	// vector to point in that direction
	/*if(mBoundingBox.top < inEntity->mBoundingBox.bottom && mBoundingBox.left > inEntity->mBoundingBox.left && mBoundingBox.right < inEntity->mBoundingBox.right)
	{
		dirVec = Y_UNIT_NEGATIVE;
	}
	else if(mBoundingBox.bottom < inEntity->mBoundingBox.top && mBoundingBox.left > inEntity->mBoundingBox.left && mBoundingBox.right < inEntity->mBoundingBox.right)
	{
		dirVec = Y_UNIT_POSITIVE;
	}
	else if(mBoundingBox.left < inEntity->mBoundingBox.right && mBoundingBox.right > inEntity->mBoundingBox.left)
	{
		dirVec = X_UNIT_NEGATIVE;
	}
	else if(mBoundingBox.right < inEntity->mBoundingBox.left && mBoundingBox.right > inEntity->mBoundingBox.left)
	{
		dirVec = X_UNIT_POSITIVE;
	}*/

	// Check if the position of the ball is higher than the blocks position + half its scale


	// Ball hitting the right side of the block
	// If the ball is between the right and left edges of the block
	// and if the ball is to the right of the block
	// and if the ball is between the top and bottom edges of the block
	//if(inSimulatedBoundingBox.left <= inEntity->mBoundingBox.right && inSimulatedBoundingBox.right > inEntity->mBoundingBox.left &&
		if(GetPosition().x > inEntity->mBoundingBox.right)// &&
		//inSimulatedBoundingBox.bottom < inEntity->mBoundingBox.top && inSimulatedBoundingBox.top > inEntity->mBoundingBox.bottom)
	{
		dirVec = X_UNIT_POSITIVE;
	}
	//else if(inSimulatedBoundingBox.right >= inEntity->mBoundingBox.left && inSimulatedBoundingBox.left < inEntity->mBoundingBox.right &&
		else if(GetPosition().x < inEntity->mBoundingBox.left)// &&
		//inSimulatedBoundingBox.bottom < inEntity->mBoundingBox.top && inSimulatedBoundingBox.top > inEntity->mBoundingBox.bottom)
	{
		dirVec = X_UNIT_NEGATIVE;
	}
	//else if(inSimulatedBoundingBox.bottom <= inEntity->mBoundingBox.top && inSimulatedBoundingBox.top > inEntity->mBoundingBox.bottom &&
		else if(GetPosition().y > inEntity->mBoundingBox.top)// &&
		//inSimulatedBoundingBox.right > inEntity->mBoundingBox.left && inSimulatedBoundingBox.left < inEntity->mBoundingBox.right)
	{
		dirVec = Y_UNIT_POSITIVE;
	}
	//else if(inSimulatedBoundingBox.top <= inEntity->mBoundingBox.bottom && inSimulatedBoundingBox.bottom < inEntity->mBoundingBox.top &&
		else if(GetPosition().y < inEntity->mBoundingBox.bottom)// &&
		//inSimulatedBoundingBox.right > inEntity->mBoundingBox.left && inSimulatedBoundingBox.left < inEntity->mBoundingBox.right)
	{
		dirVec = Y_UNIT_NEGATIVE;
	}

	std::cout << "before " << dirVec.x << std::endl;

	dirVec = glm::normalize(dirVec);
	Vector3 velocityNorm = glm::normalize(mVelocity);
	//inCollisionVector = glm::normalize(inCollisionVector);

	//current
	//mVelocity = (-2 * glm::dot(mVelocity, X_UNIT_POSITIVE)) * dirVec - mVelocity;

	//-2*(V dot N)*N + V
	//mVelocity = -(glm::dot(velocityNorm, dirVec) * dirVec + velocityNorm);
	//mVelocity *= -2;

	//inCollisionVector = glm::normalize(inCollisionVector);

	//Vector3 colVec = 2 * (glm::dot(inCollisionVector, dirVec)) * dirVec + inCollisionVector;


	//mVelocity = glm::normalize(colVec) * mVelocity;

	mVelocity = (-2 * (glm::dot(velocityNorm, dirVec)) * dirVec - velocityNorm);

	inCollisionVector *= 4;
	mVelocity += inCollisionVector;



	//mVelocity = glm::normalize((glm::dot(dirVec, -inCollisionVector) * dirVec) - inCollisionVector);
	//mVelocity *= -2;

	std::cout << "after" << std::endl;
	//mVelocity *= mSpeed;

	//mVelocity = -2 * (glm::dot(mVelocity, inCollisionVector)) * inCollisionVector - mVelocity;
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
		//mVelocity = -mVelocity;

		if(GetPosition().y >= 0.95f)
		{
			mVelocity.y = -mVelocity.y;
			//mVelocity = -2 * (glm::dot(mVelocity, Y_UNIT_NEGATIVE)) * Y_UNIT_NEGATIVE + mVelocity;
			//mVelocity = -(glm::dot(glm::normalize(mVelocity), Y_UNIT_NEGATIVE) * Y_UNIT_NEGATIVE + glm::normalize(mVelocity));
			//mVelocity = (-2 * (glm::dot(glm::normalize(mVelocity), Y_UNIT_NEGATIVE)) * Y_UNIT_NEGATIVE - glm::normalize(mVelocity));
		}

		if(GetPosition().y <= -0.95f)
		{
			//flip the y
			//mVelocity.y = -mVelocity.y;

			//mVelocity = -2 * (glm::dot(mVelocity, Y_UNIT_POSITIVE)) * Y_UNIT_POSITIVE + mVelocity;

			//float f = glm::dot(glm::normalize(mVelocity), Y_UNIT_POSITIVE);
			//mVelocity = (-2 * (glm::dot(glm::normalize(mVelocity), Y_UNIT_POSITIVE)) * Y_UNIT_POSITIVE - glm::normalize(mVelocity));
			//mVelocity *= -2;
		}

		if(GetPosition().x >= 0.95f)
		{
			mVelocity.x = -mVelocity.x;
			//mVelocity = -2 * (glm::dot(mVelocity, X_UNIT_NEGATIVE)) * X_UNIT_NEGATIVE + mVelocity;
			//mVelocity = (-2 * (glm::dot(glm::normalize(mVelocity), X_UNIT_NEGATIVE)) * X_UNIT_NEGATIVE - glm::normalize(mVelocity));
			//mVelocity = -(glm::dot(glm::normalize(mVelocity), X_UNIT_NEGATIVE) * X_UNIT_NEGATIVE + glm::normalize(mVelocity));
		}

		if(GetPosition().x <= -0.95f)
		{
			//flip the x

			mVelocity.x = -mVelocity.x;

			//mVelocity = -2 * (glm::dot(mVelocity, X_UNIT_POSITIVE)) * X_UNIT_POSITIVE + mVelocity;

			//mVelocity = (-2 * (glm::dot(glm::normalize(mVelocity), X_UNIT_POSITIVE)) * X_UNIT_POSITIVE - glm::normalize(mVelocity));

			//mVelocity = -(glm::dot(glm::normalize(mVelocity), X_UNIT_POSITIVE) * X_UNIT_POSITIVE + glm::normalize(mVelocity));
		}
	}

	//std::cout << "Ball posx: " << GetPosition().x << std::endl;
	//std::cout << "Ball posy: " << GetPosition().y << std::endl;

	if(mMovementEnabled)
	{
		MovePosition(glm::normalize(mVelocity) * mSpeed * inDT);
	}
}