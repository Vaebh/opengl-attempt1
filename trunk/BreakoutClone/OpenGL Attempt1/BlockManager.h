#ifndef BLOCKMANAGER_SIMENGINE
#define BLOCKMANAGER_SIMENGINE

#include "Block.h"
#include "Scene.h"
#include <vector>

class BlockManager
{
public:
	BlockManager(Scene* inScene, std::string instrLevelLayout);
	~BlockManager();

	void Update(float inDT);

private:
	Block* mBlocks[3][3];
};

#endif