#include "BlockManager.h"

BlockManager::BlockManager(Scene* inScene, std::string instrLevelLayout)
{
	for(int i = 0; i < BLOCK_COLS; ++i)
	{
		for(int j = 0; j < BLOCK_ROWS; ++j)
		{
			mBlocks[i][j] = new Block;
			inScene->AddToScene(mBlocks[i][j]);

			mBlocks[i][j]->mScale = Vector3(0.2, 0.2, 0);
			mBlocks[i][j]->SetPosition(Vector3(-0.8f + i * 0.3f, 0.8f - j * 0.3f, 0.f));
		}
	}
}

BlockManager::~BlockManager()
{
	for(int i = 0; i < BLOCK_COLS; ++i)
	{
		for(int j = 0; j < BLOCK_ROWS; ++j)
		{
			delete mBlocks[i][j];
			mBlocks[i][j] = 0;
		}
	}
}

void BlockManager::Update(float inDT)
{
	for(int i = 0; i < BLOCK_COLS; ++i)
	{
		for(int j = 0; j < BLOCK_ROWS; ++j)
		{
			if(mBlocks[i][j] != NULL)
			{
				mBlocks[i][j]->Update(inDT);
				if(mBlocks[i][j]->mDead)
				{
					delete mBlocks[i][j];
					mBlocks[i][j] = 0;
				}
			}
		}
	}
}