#ifndef STATE_LEVEL_ONE_SIMENGINE
#define STATE_LEVEL_ONE_SIMENGINE

#include "State.h"
#include "Sprite.h"
#include "BlockManager.h"
#include "Ball.h"

#include "Input.h"

class StateLevelOne : public IState
{
public:
	StateLevelOne();
	~StateLevelOne();

	virtual void Update(float inDT);

private:
	BlockManager* mBlockManager;
	GameObject* mBall;

	GameObject* mPaddle;
};

#endif