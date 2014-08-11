#ifndef BLOCKMANAGER_SIMENGINE
#define BLOCKMANAGER_SIMENGINE

#include "../Structure/GameObject.h"
#include <vector>

const int BLOCK_COLS = 6;
const int BLOCK_ROWS = 4;

class BlockManager
{
public:
	BlockManager(std::vector<GameObject*>& outGameObjects, std::string instrLevelLayout);
	~BlockManager();

	void Update(float inDT);

private:
	GameObject* mBlocks[BLOCK_COLS][BLOCK_ROWS];
};

#endif