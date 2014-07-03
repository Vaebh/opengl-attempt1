#ifndef GAMEOBJECT_SIMENGINE
#define GAMEOBJECT_SIMENGINE

#include "Component.h"
#include "Vectors.h"

#include <vector>

class IComponent;

class GameObject
{
public:
	GameObject();

	void Attach(IComponent* inComponent);
	void Detach(IComponent* inComponent);

	void Update(float inDT);

public:
	unsigned const int mIndex;
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 mRotationAngle;

	// TODO USE VELOCITY FOR MOVEMENT IN UPDATE

	Vector3 mVelocity;

private:
	static unsigned int mNumGameObjects;
	std::vector<IComponent*> mComponents;
};

#endif