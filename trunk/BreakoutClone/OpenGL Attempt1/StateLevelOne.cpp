#include "StateLevelOne.h"
#include "Render.h"
#include "Paddle.h"

StateLevelOne::StateLevelOne(Scene* inScene) : IState(inScene)
{
	mBall = new Ball(Vector3(-0.2, -0.7, 0));
	mBall->mScale = Vector3(0.1, 0.1, 0);
	inScene->AddToScene(mBall);

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