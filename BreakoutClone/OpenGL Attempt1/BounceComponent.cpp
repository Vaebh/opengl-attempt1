#include "BounceComponent.h"
#include "RenderSystem.h"
#include "EventMessenger.h"
#include <iostream>

namespace
{
	void HandleEventFree(uint32_t inEventType)
	{
		if(inEventType == BALL_COLLISION)
		{
			std::cout << "\nBALL COLLIDED YO FUCK YEAH FREE FUNCTION\n";
		}
	}
}

BounceComponent::BounceComponent(float inBounceSpeed) :
CollisionComponent(),
mBounceSpeed(inBounceSpeed),
mInitialPosition(Vector3()),
mMovementEnabled(false)
{
	// Example event usage
	IEventCallback* newCallback = new EventCallbackMember<BounceComponent>(this, &BounceComponent::HandleEvent);
	//newCallback(BALL_COLLISION);

	IEventCallback* newCallbackFree = new EventCallbackFree(&HandleEventFree);
	//newCallbackFree(BALL_COLLISION);

	EventMessenger::GetSingleton()->SubscribeToEvent(BALL_COLLISION, newCallback);
	EventMessenger::GetSingleton()->SubscribeToEvent(BALL_COLLISION, newCallbackFree);
}

void BounceComponent::HandleEvent(uint32_t inEventType)
{
	if(inEventType == BALL_COLLISION)
	{
		std::cout << "\nBALL COLLIDED YO\n" << std::endl;
	}
}

void BounceComponent::OnAttached(GameObject* inGameObject)
{
	CollisionComponent::OnAttached(inGameObject);

	mInitialPosition = inGameObject->GetPosition();
}

void BounceComponent::OnCollision(CollisionComponent* inComponent, Vector3 inCollisionVector)
{
	mMovementEnabled = true;

	Vector3 dirVec(0.f, -1.f, 0.f);

	if(mOwner->GetPosition().x > inComponent->mBoundingBox.right)// &&
	{
		dirVec = X_UNIT_POSITIVE;
	}
	else if(mOwner->GetPosition().x < inComponent->mBoundingBox.left)// &&
	{
		dirVec = X_UNIT_NEGATIVE;
	}
	else if(mOwner->GetPosition().y > inComponent->mBoundingBox.top)// &&
	{
		dirVec = Y_UNIT_POSITIVE;
	}
	else if(mOwner->GetPosition().y < inComponent->mBoundingBox.bottom)// &&
	{
		dirVec = Y_UNIT_NEGATIVE;
	}

	if(mOwner->mVelocity != Vector3())
	{
		// Reflect the balls velocity based on what side of the bounding box it hits
		Vector3 velocityNorm = glm::normalize(mOwner->mVelocity);
		mOwner->mVelocity = (-2 * (glm::dot(velocityNorm, dirVec)) * dirVec - velocityNorm);
	}

	// Add offset vector so bounces further from the center deflect more
	inCollisionVector *= 4;
	mOwner->mVelocity += inCollisionVector;

	mOwner->mVelocity = glm::normalize(mOwner->mVelocity) * mBounceSpeed;

	EventMessenger::GetSingleton()->RecordEvent(BALL_COLLISION);
}

void BounceComponent::Update(float inDT)
{
	// TODO
	// This shouldn't be here, but I can't be arsed thinking through where else to put it

	if(mOwner->GetPosition().y >= 0.95f || mOwner->GetPosition().y <= -0.95f || mOwner->GetPosition().x >= 0.95f || mOwner->GetPosition().x <= -0.95f)
	{
		if(mOwner->GetPosition().y >= 0.95f)
		{
			mOwner->mVelocity.y = -mOwner->mVelocity.y;
		}

		if(mOwner->GetPosition().y <= -0.95f)
		{

		}

		if(mOwner->GetPosition().x >= 0.95f)
		{
			mOwner->mVelocity.x = -mOwner->mVelocity.x;
		}

		if(mOwner->GetPosition().x <= -0.95f)
		{
			//flip the x
			mOwner->mVelocity.x = -mOwner->mVelocity.x;
		}
	}

	if(glfwGetKey(RenderSystem::mWindow, GLFW_KEY_1))
	{
		mOwner->mVelocity += Vector3(-0.01f, 0.f, 0.f);
	}

	if(mMovementEnabled && (mOwner->GetPosition().y <= -1.2f || glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_C)))
	{
		mOwner->mVelocity = Vector3();
		mMovementEnabled = false;
		mOwner->SetPosition(mInitialPosition);
	}

	if(!mMovementEnabled && glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_SPACE))
	{
		mOwner->mVelocity = Vector3(0.f, 0.9f, 0.f);

		mMovementEnabled = true;
	}
}