#ifndef COMPONENT_BALL_MODEL_SIMENGINE
#define COMPONENT_BALL_MODEL_SIMENGINE

#include "GameObject.h"

class ComponentBallModel : public IComponent
{
public:
	BallModel(Vector3 inPosition);
	~BallModel();

	virtual void OnCollision(Entity* inEntity, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox);
	virtual void Update(float inDT);
	virtual void Draw();

	Vector3 mVelocity;

	bool mMovementEnabled;

	Vector3 mInitialPosition;
	Vector3 mSpeed;
};

#endif