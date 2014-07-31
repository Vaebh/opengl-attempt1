#ifndef BREAKOUT_FACTORY_SIMENGINE
#define BREAKOUT_FACTORY_SIMENGINE

#include "GameObject.h"

GameObject* CreateBall();
GameObject* CreatePaddle();
GameObject* CreateBlock(Vector3 inPosition);

#endif