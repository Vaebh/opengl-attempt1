#ifndef BLOCKMANAGER_SIMENGINE
#define BLOCKMANAGER_SIMENGINE

#include "Block.h"
#include "Scene.h"
#include <vector>

const int BLOCK_COLS = 6;
const int BLOCK_ROWS = 4;

class BlockManager
{
public:
	BlockManager(Scene* inScene, std::string instrLevelLayout);
	~BlockManager();

	void Update(float inDT);

private:
	Block* mBlocks[BLOCK_COLS][BLOCK_ROWS];
};

#endif