#include "Scene.h"

class IState
{
public:
	IState(Scene* inScene) {mScene = inScene;}
	virtual void Update(float inDT) = 0;

protected:
	Scene* mScene;
};