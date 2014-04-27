#include "Scene.h"

Scene::Scene()
{

}

void Scene::AddToScene(Entity* inEntity)
{
	if(inEntity)
	{
		mEntities.push_back(inEntity);
	}
}

void Scene::Update(float inDT)
{
	for each(Entity* theEntity in mEntities)
	{
		theEntity->Update(inDT);
	}
}