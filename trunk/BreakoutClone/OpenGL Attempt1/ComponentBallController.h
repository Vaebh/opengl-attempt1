#ifndef BALL_SIMENGINE
#define BALL_SIMENGINE

#include "Sprite.h"

class Ball : public Sprite
{
public:
	Ball(Vector3 inPosition);
	~Ball();

	virtual void OnCollision(Entity* inEntity, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox);
	virtual void Update(float inDT);
	virtual void Draw();

	Vector3 mVelocity;

	bool mMovementEnabled;

	Vector3 mInitialPosition;
	Vector3 mSpeed;
};

#endif