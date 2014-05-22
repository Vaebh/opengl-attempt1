#include "Entity.h"
#include "Render.h"

Entity::Entity() :
mbVisible(true)
,mName("")
,mPosition(0.0, 0.0, 0.0)
,mScale(1.0, 1.0, 1.0)
,mRotationAngle(0)
,mInput(NULL)
,mScene(NULL)
,mShader(NULL)
,mCollidable(true)
{
	Render::GetSingleton()->AddEntity(this);
}

Entity::~Entity()
{
	Render::GetSingleton()->RemoveEntity(this);
   
   if(mScene)
   {
	mScene->RemoveFromScene(this);
   }
}

void Entity::MovePosition(Vector3 inMovement)
{
	Vector3 nextPosition = mPosition + inMovement;
	Rectangle nextPosBox = CreateBoundingBox(nextPosition);

	if(mScene && !mScene->IsColliding(nextPosBox, this))
	{
		mPosition += inMovement;
	}
}

Rectangle Entity::CreateBoundingBox(Vector3 inPosition)
{
	Rectangle theBoundingBox;

	theBoundingBox.left = inPosition.x - mScale.x / 2;
	theBoundingBox.right = inPosition.x + mScale.x / 2;

	theBoundingBox.top = inPosition.y + mScale.y / 2;
	theBoundingBox.bottom = inPosition.y - mScale.y / 2;

	return theBoundingBox;
}

void Entity::OnCollision(Entity* inEntity, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox)
{

}

void Entity::Draw()
{

}

void Entity::Update(float inDT)
{
	mBoundingBox = CreateBoundingBox(mPosition);

	if(mInput)
	{
		mInput->Update(inDT);
	}
}