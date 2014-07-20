#include "StateLevelOne.h"
#include "RenderSystem.h"
#include "BreakoutFactory.h"
#include "Foundation.h"
#include "EventMessenger.h"
#include "ComponentBallController.h"

// TODO - CONVERT THIS OVER ONCE NEW STUFF IS DONE

StateLevelOne::StateLevelOne()
{
	mBall = CreateBall();
	mGameObjects.push_back(mBall);

	mPaddle = CreatePaddle();
	mGameObjects.push_back(mPaddle);

	ComponentBallController* ballController = mBall->GetComponent<ComponentBallController>();
	if(ballController)
	{
		ballController->SetAimingObject(mPaddle);
	}

	IEventCallback* newCallbackMember = new EventCallbackMember<StateLevelOne>(this, &StateLevelOne::HandleEvent);
	EventMessenger::GetSingleton()->SubscribeToEvent(COLLISION, mPaddle, newCallbackMember);
	EventMessenger::GetSingleton()->SubscribeToEvent(COLLISION, mBall, newCallbackMember);

	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_PRESS, mBall, newCallbackMember);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_RELEASE, mBall, newCallbackMember);

	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_W_PRESS, mBall, newCallbackMember);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_W_RELEASE, mBall, newCallbackMember);

	mBlockManager = new BlockManager(mGameObjects, "");
}

StateLevelOne::~StateLevelOne()
{
	SAFE_DELETE(mBlockManager);
	SAFE_DELETE(mBall);
	SAFE_DELETE(mPaddle);
}

void StateLevelOne::HandleEvent(uint32_t inEventType, GameObject* inTarget)
{
	if(inEventType == INPUT_SPACE_PRESS)
	{
		std::cout << "Space bar pressed!=============\n";
	}
	if(inEventType == INPUT_SPACE_RELEASE)
	{
		std::cout << "Space bar released!=============\n";
	}

	if(inEventType == INPUT_W_PRESS)
	{
		std::cout << "W pressed!=============\n";
	}
	if(inEventType == INPUT_W_RELEASE)
	{
		std::cout << "W released!=============\n";
	}

	if(inEventType == COLLISION && inTarget == mPaddle)
	{
		std::cout << "=============PADDLE COLLIDED=============\n";
	}
	else if(inEventType == COLLISION && inTarget == mBall)
	{
		std::cout << "=============BALL COLLIDED=============\n";
	}
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