#include "Block.h"

Block::Block() : Sprite("sample.png"), mHealth(2)
{
	
}

void Block::OnCollision()
{
	mHealth -= 1;
}

void Block::Update(float inDT)
{
	Sprite::Update(inDT);
}