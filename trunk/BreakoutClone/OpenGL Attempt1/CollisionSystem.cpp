#include "CollisionSystem.h"

// TODO - DECIDE WHERE COLLISION IS HAPPENING AND HOW TO USE IT TO PREVENT MOVEMENT
// TODO - ADD POSITION MANIPULATION METHODS TO GAMEOBJECT AND HAVE THEM CHECK COLLISION FIRST

CollisionSystem* CollisionSystem::mColSystem = NULL;

CollisionSystem* CollisionSystem::GetSingleton()
{
	if(mColSystem == NULL)
	{
		mColSystem = new CollisionSystem();
	}

	return mColSystem;
}

// These two methods should be abstract in System.h
void CollisionSystem::AddComponent(CollisionComponent* inCollisionComponent)
{
	if(inCollisionComponent)
	{
		mComponents.push_back(inCollisionComponent);
	}
}

void CollisionSystem::RemoveComponent(CollisionComponent* inCollisionComponent)
{
	if(inCollisionComponent)
	{
		std::vector<CollisionComponent*>::const_iterator it;

		for(it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			if((*it) == inCollisionComponent)
			{
				mComponents.erase(it);

				// Downsize the vector
				std::vector<CollisionComponent*>(mComponents).swap(mComponents);
				break;
			}
		}
	}
}

bool CollisionSystem::IsColliding(Rectangle inBoundingBox, CollisionComponent* inCollisionComponent)
{
	for each(CollisionComponent* theComponent in mComponents)
	{
		if(theComponent != inCollisionComponent && theComponent->IsIntersecting(inBoundingBox))
		{
			Vector3 GameObject1Center = Vector3(inCollisionComponent->mOwner->GetPosition().x + inCollisionComponent->mOwner->mScale.x / 2, inCollisionComponent->mOwner->GetPosition().y + inCollisionComponent->mOwner->mScale.y / 2, 0.f);
			Vector3 GameObject2Center = Vector3(theComponent->mOwner->GetPosition().x + theComponent->mOwner->mScale.x / 2, theComponent->mOwner->GetPosition().y + theComponent->mOwner->mScale.y / 2, 0.f);

			Vector3 collisionVector = inCollisionComponent->mOwner->GetPosition() - theComponent->mOwner->GetPosition();

			theComponent->OnCollision(inCollisionComponent, collisionVector);
			inCollisionComponent->OnCollision(theComponent, collisionVector);
			return true;
		}
	}

	return false;
}

void CollisionSystem::Update(float inDT)
{
	/*for(std::vector<CollisionComponent*>::const_iterator it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if(*it)
		{
			(*it)->Update(inDT);
		}
	}*/
}