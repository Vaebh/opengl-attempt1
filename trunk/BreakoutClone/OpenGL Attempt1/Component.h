#ifndef COMPONENT_SIMENGINE
#define COMPONENT_SIMENGINE

#include "GameObject.h"

class GameObject;

class IComponent
{
public:
	IComponent();
	virtual void Update(float inDT) = 0;

	inline GameObject* GetOwner() const {return mOwner;}
	inline void SetOwner(GameObject* inNewOwner) {mOwner = inNewOwner;}

private:
	GameObject* mOwner;
};

#endif