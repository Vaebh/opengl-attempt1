#ifndef BLOCK_SIMENGINE
#define BLOCK_SIMENGINE

#include "Sprite.h"

class Block : public Sprite
{
public:
	Block();

	virtual void OnCollision(Entity* inEntity, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox);
	virtual void Update(float inDT);

	int mHealth;
	bool mDying;
	bool mDead;
};

#endif