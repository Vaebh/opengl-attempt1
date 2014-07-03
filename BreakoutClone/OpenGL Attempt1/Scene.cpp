#include "Scene.h"

// TODO - PROBABLY GET RID OF THIS< BUT COMMENT IT OUT FOR NOW

Scene::Scene()
{

}

bool Scene::IsColliding(Rectangle inBoundingBox, Entity* inEntity)
{
	for each(Entity* theEntity in mEntities)
	{
		if(theEntity != inEntity && theEntity->mCollidable && IsIntersecting(inBoundingBox, theEntity->mBoundingBox))
		{
			Vector3 entity1Center = Vector3(inEntity->GetPosition().x + inEntity->mScale.x / 2, inEntity->GetPosition().y + inEntity->mScale.y / 2, 0.f);
			Vector3 entity2Center = Vector3(theEntity->GetPosition().x + theEntity->mScale.x / 2, theEntity->GetPosition().y + theEntity->mScale.y / 2, 0.f);

			Vector3 collisionVector = inEntity->GetPosition() - theEntity->GetPosition();//entity1Center - entity2Center;

			//collisionVector *= 4;

			theEntity->OnCollision(inEntity, collisionVector, theEntity->mBoundingBox);
			inEntity->OnCollision(theEntity, collisionVector, inBoundingBox);
			return true;
		}
	}

	return false;
}

bool Scene::IsIntersecting(Rectangle inA, Rectangle inB)
{
	if(inA.right > inB.left && inA.left < inB.right &&
		inA.bottom < inB.top && inA.top > inB.bottom)
	{
		return true;
	}

	return false;
}

void Scene::AddToScene(Entity* inEntity)
{
	if(inEntity)
	{
		mEntities.push_back(inEntity);
		inEntity->SetOwningScene(const_cast<Scene*>(this));
	}
}

void Scene::RemoveFromScene(Entity* inEntity)
{
	if(inEntity)
	{
		std::vector<Entity*>::const_iterator iter;

		for(iter = mEntities.begin(); iter != mEntities.end(); ++iter)
		{
			if(*iter == inEntity)
			{
				mEntities.erase(iter);
				break;
			}
		}
	}
}

void Scene::Update(float inDT)
{
	for each(Entity* theEntity in mEntities)
	{
		theEntity->Update(inDT);
	}
}