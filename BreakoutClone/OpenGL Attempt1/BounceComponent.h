#ifndef BOUNCE_COMPONENT_SIMENGINE
#define BOUNCE_COMPONENT_SIMENGINE

#include "CollisionComponent.h"
#include "EventMessenger.h"

class BounceComponent : public CollisionComponent
{
public:
	BounceComponent(float inBounceSpeed);

	void OnCollision(CollisionComponent* inComponent, Vector3 inCollisionVector);

	void Update(float inDT);

	void OnAttached(GameObject* inGameObject);

	//void HandleEvent(EventType inEventType);

public:
	Vector3 mInitialPosition;

private:
	float mBounceSpeed;
	bool mMovementEnabled;
};

#endif