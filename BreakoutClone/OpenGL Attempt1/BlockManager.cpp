#include "BlockManager.h"

BlockManager::BlockManager(Scene* inScene, std::string instrLevelLayout)
{
	for(int i = 0; i < 3; ++i)
	{
   //std::vector<Block*> newVector;
   //mBlocks.push_back(newVector);
		for(int j = 0; j < 3; ++j)
		{
			Block* newBlock = new Block();
			mBlocks[i][j] = newBlock;
      //newVector.push_back(newBlock);
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
      //if(mBlocks[i][j] != NULL)
      //{
			delete mBlocks[i][j];
			mBlocks[i][j] = 0;
         //}
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
				if(mBlocks[i][j]->mHealth <= 0)
				{
					delete mBlocks[i][j];
					mBlocks[i][j] = 0;
				}
			}
		}
	}
}