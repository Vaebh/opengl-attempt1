#ifndef STATE_LEVEL_ONE_SIMENGINE
#define STATE_LEVEL_ONE_SIMENGINE

#include "../Structure/State.h"
#include "../Game/BlockManager.h"
#include "../Foundation/Foundation.h"

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