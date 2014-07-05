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
	~GameObject();

	void Attach(IComponent* inComponent);
	void Detach(IComponent* inComponent);

	inline Vector3 GetPosition() const {return mPosition;}
	inline void SetPosition(Vector3 inPosition) {mPosition = inPosition;}
	void MovePosition(Vector3 inPosition);

	void ScaleBy(Vector3 inScale) {mScale += inScale;}

	void Update(float inDT);

public:
	unsigned const int mIndex;
	Vector3 mScale;
	Vector3 mRotationAngle;

	// TODO USE VELOCITY FOR MOVEMENT IN UPDATE

	Vector3 mVelocity;

	std::vector<IComponent*> mComponents;

	std::string mName;

private:
	static unsigned int mNumGameObjects;

	Vector3 mPosition;
};

#endif