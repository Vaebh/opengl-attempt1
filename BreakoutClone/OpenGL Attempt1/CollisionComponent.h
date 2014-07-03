#ifndef COLLISION_COMPONENT_SIMENGINE
#define COLLISION_COMPONENT_SIMENGINE

#include "Component.h"
#include "Rectangle.h"

class CollisionComponent : public IComponent
{
public:
	CollisionComponent();
	virtual void Update(float inDT);

	bool IsColliding(Rectangle inBoundingBox, GameObject* inGameObject);

	virtual void OnAttached();
	void OnCollision(GameObject* inGameObject, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox);

	bool IsIntersecting(Rectangle inA);

public:
	Rectangle mBoundingBox;

private:
	void CreateBoundingBox(Vector3 inPosition);
};

#endif