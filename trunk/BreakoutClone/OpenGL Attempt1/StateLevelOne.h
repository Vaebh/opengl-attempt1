#include "State.h"
#include "Sprite.h"
#include "BlockManager.h"
#include "Ball.h"

#include "Input.h"

class StateLevelOne : public IState
{
public:
	StateLevelOne(Scene* inScene);
	~StateLevelOne();

	virtual void Update(float inDT);

private:
	BlockManager* mBlockManager;
	Ball* mBall;

	Sprite* mPlayer;
};