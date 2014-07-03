#include "CollisionComponent.h"

bool CollisionComponent::IsIntersecting(Rectangle inA)
{
	Rectangle RectB = mBoundingBox;

	if(inA.right > RectB.left && inA.left < RectB.right &&
		inA.bottom < RectB.top && inA.top > RectB.bottom)
	{
		return true;
	}

	return false;
}

void CollisionComponent::OnAttached()
{
	CreateBoundingBox(mOwner->mPosition);
}

void CollisionComponent::CreateBoundingBox(Vector3 inPosition)
{
	mBoundingBox.left = inPosition.x - mOwner->mScale.x / 2;
	mBoundingBox.right = inPosition.x + mOwner->mScale.x / 2;

	mBoundingBox.top = inPosition.y + mOwner->mScale.y / 2;
	mBoundingBox.bottom = inPosition.y - mOwner->mScale.y / 2;
}

void CollisionComponent::OnCollision(GameObject* inGameObject, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox)
{

}