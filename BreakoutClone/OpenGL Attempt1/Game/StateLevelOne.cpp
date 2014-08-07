#include "../Game/StateLevelOne.h"
#include "../Rendering/RenderSystem.h"
#include "../Game/BreakoutFactory.h"
#include "../Foundation/Foundation.h"
#include "../Events/EventMessenger.h"
#include "../Game/ComponentBallController.h"
#include "../Rendering/SpriteComponent.h"

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
	if(inEventType == COLLISION && inTarget == mPaddle.get())
	{
		//std::cout << "=============PADDLE COLLIDED=============\n";
	}
	else if(inEventType == COLLISION && inTarget == mBall.get())
	{
		//std::cout << "=============BALL COLLIDED=============\n";

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