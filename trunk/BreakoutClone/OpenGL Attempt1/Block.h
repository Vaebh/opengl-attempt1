#include "Sprite.h"

class Block : public Sprite
{
public:
	Block();

	virtual void OnCollision();
	virtual void Update(float inDT);

	int mHealth;
};