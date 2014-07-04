#include "Scene.h"

// TODO - PROBABLY GET RID OF THIS, BUT COMMENT IT OUT FOR NOW

Scene::Scene()
{

}

void Scene::AddToScene(GameObject* inGameObject)
{
	if(inGameObject)
	{
		mGameObjects.push_back(inGameObject);
		inGameObject->SetOwningScene(const_cast<Scene*>(this));
	}
}

void Scene::RemoveFromScene(inGameObject* ininGameObject)
{
	if(inGameObject)
	{
		std::vector<inGameObject*>::const_iterator iter;

		for(iter = mGameObjects.begin(); iter != mGameObjects.end(); ++iter)
		{
			if(*iter == inGameObject)
			{
				mGameObjects.erase(iter);
				break;
			}
		}
	}
}

void Scene::Update(float inDT)
{
	for each(GameObject* theGameObject in mGameObjects)
	{
		theGameObject->Update(inDT);
	}
}