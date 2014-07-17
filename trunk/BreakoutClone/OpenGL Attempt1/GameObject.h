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

	inline const std::string GetName() {return mName;}
	inline void SetName(std::string inName) {mName = inName;}

	void Update(float inDT);

	template<class ComponentType>
	ComponentType* GetComponent();

public:
	unsigned const int mIndex;
	Vector3 mScale;
	Vector3 mRotationAngle;
	Vector3 mVelocity;

	std::vector<IComponent*> mComponents;

private:
	static unsigned int mNumGameObjects;

	Vector3 mPosition;
	std::string mName;
};

template<class ComponentType>
ComponentType* GetComponent()
{
	for each(IComponent* theComponent in mComponents)
	{
		ComponentType* soughtComp = dynamic_cast<ComponentType*>(theComponent);

		if(soughtComp != NULL)
		{
			return soughtComp;
		}
	}

	return NULL;
}

#endif