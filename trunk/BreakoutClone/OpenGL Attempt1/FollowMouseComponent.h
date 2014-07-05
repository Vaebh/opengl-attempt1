#ifndef FOLLOWMOUSE_COMPONENT_SIMENGINE
#define FOLLOWMOUSE_COMPONENT_SIMENGINE

#include "Component.h"

enum AXIS
{
	X_AXIS,
	Y_AXIS,
	BOTH_AXIS
};

class FollowMouseComponent : public IComponent
{
public:
	FollowMouseComponent(AXIS inAxis);

	void Update(float inDT);

private:
	AXIS mAxis;
};

#endif