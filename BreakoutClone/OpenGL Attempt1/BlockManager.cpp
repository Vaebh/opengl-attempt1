#include "BlockManager.h"
#include "BreakoutFactory.h"
#include "FragileCollisionComponent.h"
#include <sstream>

std::string convertInt(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

#include "SpriteComponent.h"

BlockManager::BlockManager(std::vector<GameObject*>& outGameObjects, std::string instrLevelLayout)
{
	for(int i = 0; i < BLOCK_COLS; ++i)
	{
		for(int j = 0; j < BLOCK_ROWS; ++j)
		{
			//mBlocks[i][j] = CreateBlock();
			mBlocks[i][j] = new GameObject();

			mBlocks[i][j]->mScale = Vector3(0.2, 0.2, 0);
			mBlocks[i][j]->SetPosition(Vector3(-0.8f + i * 0.3f, 0.8f - j * 0.3f, 0.f));

			SpriteComponent* spriteComp = new SpriteComponent("bros.png", 1);
			mBlocks[i][j]->Attach(spriteComp);

			FragileCollisionComponent* fragileColComp = new FragileCollisionComponent();
			mBlocks[i][j]->Attach(fragileColComp);

			mBlocks[i][j]->mName = "Block" + convertInt(i);

			// this stays
			//mBlocks[i][j]->SetPosition(Vector3(-0.8f + i * 0.3f, 0.8f - j * 0.3f, 0.f));

			//outGameObjects.push_back(mBlocks[i][j]);
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
						//theComponent->Update(inDT);

						mBlocks[i][j]->Update(inDT);

						if(fragComp->mDead)
						{
							delete mBlocks[i][j];
							mBlocks[i][j] = 0;

							break;
						}
					}
				}
			}
		}
	}
}