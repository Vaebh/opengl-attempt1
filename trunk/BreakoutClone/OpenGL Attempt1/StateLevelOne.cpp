#include "StateLevelOne.h"
#include "Render.h"
#include "Paddle.h"

// TODO - CONVERT THIS OVER ONCE NEW STUFF IS DONE

StateLevelOne::StateLevelOne()
{
	mBall = new Ball(Vector3(-0.2, -0.7, 0));
	mBall->mScale = Vector3(0.1, 0.1, 0);

	mBall = new GameObject();
	BounceComponent ballComp = new BounceComponent();
	mBall->Attach(ballComp);

	mGameObjects.push_back(mBall);

	mBlockManager = new BlockManager(inScene, "");

	/*mPlayer = new Sprite();
	Input* inputHandler = new Input(Render::mWindow, mBall);
	mPlayer->SetPosition(Vector3(0.4, -0.4, 0));
	mPlayer->mScale = Vector3(0.5, 0.5, 0);*/

	Paddle* thePaddle = new Paddle(mBall);
	inScene->AddToScene(thePaddle);
	Input* inputHandler = new Input(Render::mWindow, thePaddle);

	//inScene->AddToScene(mPlayer);
}

StateLevelOne::~StateLevelOne()
{
	delete mBlockManager;
	mBlockManager = 0;

	delete mBall;
	mBall = 0;

	delete mPlayer;
	mPlayer = 0;
}

void StateLevelOne::Update(float inDT)
{
	mBlockManager->Update(inDT);
}