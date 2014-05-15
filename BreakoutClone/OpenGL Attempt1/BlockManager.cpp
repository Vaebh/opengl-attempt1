#include "BlockManager.h"

BlockManager::BlockManager(Scene* inScene, std::string instrLevelLayout)
{
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			Block* newBlock = new Block();
			mBlocks[i][j] = newBlock;
			inScene->AddToScene(newBlock);

			newBlock->mScale = Vector3(0.3, 0.15, 0);
			newBlock->SetPosition(Vector3(-0.8f + i * 0.4f, 0.8f - j * 0.3f, 0.f));
		}
	}
}

BlockManager::~BlockManager()
{
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			delete mBlocks[i][j];
			mBlocks[i][j] = 0;
		}
	}
}

void BlockManager::Update(float inDT)
{
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(mBlocks[i][j] != NULL)
			{
				mBlocks[i][j]->Update(inDT);
				if(mBlocks[i][j]->mHealth <= 0)
				{
					delete mBlocks[i][j];
					mBlocks[i][j] = 0;
				}
			}
		}
	}
}