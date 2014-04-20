#include "Entity.h"

Entity::Entity() :
mbVisible(true)
,mName("")
,mPosition(0.0, 0.0, 0.0)
,mScale(1.0, 1.0, 1.0)
{
	
}

Entity::~Entity()
{

}

void Entity::Draw()
{

}

void Entity::Update(float inDeltaTime)
{
	if(mInput)
	{
		mInput->Update(inDeltaTime);
	}
}