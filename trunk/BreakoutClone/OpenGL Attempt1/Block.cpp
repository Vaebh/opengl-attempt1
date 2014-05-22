#include "Block.h"

Block::Block() : Sprite("sample.png"),
mHealth(2),
mDying(false),
mDead(false)
{
	mName = "Block";
}

void Block::OnCollision(Entity* inEntity, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox)
{
	mHealth -= 1;

	if(mHealth <= 0 && !mDying && !mDead)
	{
		mDying = true;
		mCollidable = false;
	}
}

void Block::Update(float inDT)
{
	Sprite::Update(inDT);

	if(mDying)
	{
		ScaleBy(Vector3(-0.1f * inDT, -0.1f * inDT, 0.f));
	}

	if(mScale.x <= 0.001f)
	{
		mDead = true;
	}
}