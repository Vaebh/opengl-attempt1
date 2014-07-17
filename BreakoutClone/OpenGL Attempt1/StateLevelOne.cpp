#include "StateLevelOne.h"
#include "RenderSystem.h"
#include "BreakoutFactory.h"
#include "Foundation.h"

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