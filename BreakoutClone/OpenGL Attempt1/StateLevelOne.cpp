#include "StateLevelOne.h"
#include "RenderSystem.h"
#include "BreakoutFactory.h"
#include "Foundation.h"
#include "EventMessenger.h"

// TODO - CONVERT THIS OVER ONCE NEW STUFF IS DONE

namespace
{
	void HandleEventPaddle(uint32_t inEventType)
	{
		if(inEventType == COLLISION)
		{
			std::cout << "\n=============PADDLE COLLIDED=============\n";
		}
	}
};

StateLevelOne::StateLevelOne()
{
	mBall = CreateBall();
	mGameObjects.push_back(mBall);

	mPaddle = CreatePaddle();
	mGameObjects.push_back(mPaddle);

	IEventCallback* newCallbackFree = new EventCallbackFree(&HandleEventPaddle);
	EventMessenger::GetSingleton()->SubscribeToEvent(COLLISION, mPaddle, newCallbackFree);

	mBlockManager = new BlockManager(mGameObjects, "");
}

StateLevelOne::~StateLevelOne()
{
	SAFE_DELETE(mBlockManager);
	SAFE_DELETE(mBall);
	SAFE_DELETE(mPaddle);
}

void StateLevelOne::Update(float inDT)
{
	for(std::vector<GameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
	{
		if((*it) == NULL)
		{
			it = mGameObjects.erase(it);
		}
		else
		{
			(*it)->Update(inDT);
		}
	}

	mBlockManager->Update(inDT);
}