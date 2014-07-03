#include "System.h"
#include "CollisionComponent.h"

class CollisionSystem : public ISystem
{
public:
	// TODO - TURN THESE INTO TEMPLATE METHODS
	void AddComponent(CollisionComponent* inCollisionComponent);
	void RemoveComponent(CollisionComponent* inCollisionComponent);

	void Update(float inDT);

	bool IsColliding(Rectangle inBoundingBox, CollisionComponent* inCollisionComponent);

private:
	std::vector<CollisionComponent*> mComponents;
};