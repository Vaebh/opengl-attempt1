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
			mBlocks[i][j]->SetName("Block" + ConvertNumber(i));
		}
	}
}

BlockManager::~BlockManager()
{
	for(int i = 0; i < BLOCK_COLS; ++i)
	{
		for(int j = 0; j < BLOCK_ROWS; ++j)
		{
			SAFE_DELETE(mBlocks[i][j]);
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
                for(uint32_t k = 0; k < mBlocks[i][j]->mComponents.size(); ++k)
				{
					FragileCollisionComponent* fragComp = dynamic_cast<FragileCollisionComponent*>(mBlocks[i][j]->mComponents[k]);
					if(fragComp)
					{
						mBlocks[i][j]->Update(inDT);

						if(fragComp->mDead)
						{
                            // Probably shouldn't be deleting this here, instead should be in StateLevelone
							SAFE_DELETE(mBlocks[i][j]);

							break;
						}
					}
				}
			}
		}
	}
}