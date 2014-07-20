#ifndef STATE_LEVEL_ONE_SIMENGINE
#define STATE_LEVEL_ONE_SIMENGINE

#include "State.h"
#include "BlockManager.h"
#include "Foundation.h"

#include "Input.h"

class StateLevelOne : public IState
{
public:
	StateLevelOne();
	~StateLevelOne();

	virtual void Update(float inDT);

	void HandleEvent(uint32_t inEventType, GameObject* inTarget);

private:
	BlockManager* mBlockManager;
	GameObject* mBall;
	GameObject* mPaddle;
};

#endif