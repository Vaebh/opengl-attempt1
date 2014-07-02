#ifndef STATE_SIMENGINE
#define STATE_SIMENGINE

#include "Scene.h"

class IState
{
public:
	IState(Scene* inScene) {mScene = inScene;}
	virtual void Update(float inDT) = 0;

protected:
	Scene* mScene;
};

#endif