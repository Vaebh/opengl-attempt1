#ifndef STATE_SIMENGINE
#define STATE_SIMENGINE

#include "Scene.h"
#include "GameObject.h"

class IState
{
public:
	virtual void Update(float inDT) = 0;

protected:
	std::vector<GameObject*> mGameObjects;
};

#endif