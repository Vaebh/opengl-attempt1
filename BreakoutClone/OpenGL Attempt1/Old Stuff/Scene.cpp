/*#include "Scene.h"

// TODO - PROBABLY GET RID OF THIS, BUT COMMENT IT OUT FOR NOW

Scene::Scene()
{

}

void Scene::AddToScene(Entity* inEntity)
{
	if(inEntity)
	{
		mEntitys.push_back(inEntity);
		inEntity->SetOwningScene(const_cast<Scene*>(this));
	}
}

void Scene::RemoveFromScene(Entity* inEntity)
{
	if(inEntity)
	{
		std::vector<Entity*>::const_iterator iter;

		for(iter = mEntitys.begin(); iter != mEntitys.end(); ++iter)
		{
			if(*iter == inEntity)
			{
				mEntitys.erase(iter);
				break;
			}
		}
	}
}

void Scene::Update(float inDT)
{
	for each(Entity* theEntity in mEntitys)
	{
		theEntity->Update(inDT);
	}
}*/