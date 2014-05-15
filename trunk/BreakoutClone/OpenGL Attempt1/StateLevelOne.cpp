#include "StateLevelOne.h"
#include "Render.h"

StateLevelOne::StateLevelOne(Scene* inScene) : IState(inScene)
{
	mBlockManager = new BlockManager(inScene, "");

	mBall = new Ball();
	mBall->mScale = Vector3(0.1, 0.1, 0);
	mBall->SetPosition(Vector3(-0.2, 0.5, 0));
	inScene->AddToScene(mBall);

	mPlayer = new Sprite();
	Input* inputHandler = new Input(Render::mWindow, mBall);
	mPlayer->SetPosition(Vector3(0.4, -0.4, 0));
	mPlayer->mScale = Vector3(0.5, 0.5, 0);

	inScene->AddToScene(mPlayer);
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