#include "Block.h"

Block::Block() : Sprite("sample.png"), mHealth(2)
{
	mName = "Block";
}

void Block::OnCollision()
{
	mHealth -= 1;
}

void Block::Update(float inDT)
{
	Sprite::Update(inDT);
}