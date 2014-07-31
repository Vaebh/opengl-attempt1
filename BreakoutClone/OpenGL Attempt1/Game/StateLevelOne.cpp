#include "StateLevelOne.h"
#include "RenderSystem.h"
#include "BreakoutFactory.h"
#include "Foundation.h"
#include "EventMessenger.h"
#include "ComponentBallController.h"
#include "SpriteComponent.h"

// TODO - CONVERT THIS OVER ONCE NEW STUFF IS DONE

StateLevelOne::StateLevelOne()
{
	mBall.reset(CreateBall());
	mGameObjects.push_back(mBall.get());

	mPaddle.reset(CreatePaddle());
	mGameObjects.push_back(mPaddle.get());

	ComponentBallController* ballController = mBall->GetComponent<ComponentBallController>();
	if(ballController)
	{
		ballController->SetAimingObject(mPaddle.get());
	}

	IEventCallback* newCallbackMember = new EventCallbackMember<StateLevelOne>(this, &StateLevelOne::HandleEvent);
	EventMessenger::GetSingleton()->SubscribeToEvent(COLLISION, mPaddle.get(), newCallbackMember);
	EventMessenger::GetSingleton()->SubscribeToEvent(COLLISION, mBall.get(), newCallbackMember);

	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_PRESS, mBall.get(), newCallbackMember);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_RELEASE, mBall.get(), newCallbackMember);

	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_W_PRESS, mBall.get(), newCallbackMember);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_W_RELEASE, mBall.get(), newCallbackMember);

	mBlockManager.reset(new BlockManager(mGameObjects, ""));
}

StateLevelOne::~StateLevelOne()
{
	mBlockManager.reset();
	mBall.reset();
	mPaddle.reset();
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

	if(inEventType == COLLISION && inTarget == mPaddle.get())
	{
		std::cout << "=============PADDLE COLLIDED=============\n";
	}
	else if(inEventType == COLLISION && inTarget == mBall.get())
	{
		std::cout << "=============BALL COLLIDED=============\n";

		mBall->GetComponent<SpriteComponent>()->mColourTint = Vector4(0.f, 0.f, 1.f, 0.f);
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