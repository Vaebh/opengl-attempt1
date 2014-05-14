#include "Scene.h"

Scene::Scene()
{

}

bool Scene::IsColliding(Rectangle inBoundingBox, Entity* inEntity)
{
	for each(Entity* theEntity in mEntities)
	{
		if(theEntity != inEntity && IsIntersecting(inBoundingBox, theEntity->mBoundingBox))
		{
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

void Scene::Update(float inDT)
{
	for each(Entity* theEntity in mEntities)
	{
		theEntity->Update(inDT);
	}
}