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
    std::unique_ptr<BlockManager> mBlockManager;
	std::unique_ptr<GameObject> mBall;
	std::unique_ptr<GameObject> mPaddle;
};

#endif