#include "StateLevelOne.h"
#include "RenderSystem.h"
#include "BreakoutFactory.h"

// TODO - CONVERT THIS OVER ONCE NEW STUFF IS DONE

StateLevelOne::StateLevelOne()
{
	mBall = CreateBall();
	mGameObjects.push_back(mBall);

	mPaddle = CreatePaddle();
	mGameObjects.push_back(mPaddle);

	mBlockManager = new BlockManager(mGameObjects, "");
}

StateLevelOne::~StateLevelOne()
{
	delete mBlockManager;
	mBlockManager = 0;

	delete mBall;
	mBall = 0;

	delete mPaddle;
	mPaddle = 0;
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