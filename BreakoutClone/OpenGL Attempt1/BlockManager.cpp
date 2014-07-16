#include "BlockManager.h"
#include "BreakoutFactory.h"
#include "FragileCollisionComponent.h"
#include "Foundation.h"
#include "StringUtils.h"

BlockManager::BlockManager(std::vector<GameObject*>& outGameObjects, std::string instrLevelLayout)
{
	for(int i = 0; i < BLOCK_COLS; ++i)
	{
		for(int j = 0; j < BLOCK_ROWS; ++j)
		{
			mBlocks[i][j] = CreateBlock(Vector3(-0.8f + i * 0.3f, 0.8f - j * 0.3f, 0.f));
			mBlocks[i][j]->mName = "Block" + ConvertNumber(i);
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
				for each(IComponent* theComponent in mBlocks[i][j]->mComponents)
				{
					FragileCollisionComponent* fragComp = dynamic_cast<FragileCollisionComponent*>(theComponent);
					if(fragComp)
					{
						mBlocks[i][j]->Update(inDT);

						if(fragComp->mDead)
						{
							SAFE_DELETE(mBlocks[i][j]);

							break;
						}
					}
				}
			}
		}
	}
}