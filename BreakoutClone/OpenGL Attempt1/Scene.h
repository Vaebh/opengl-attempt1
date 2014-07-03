#ifndef SCENE_SIMENGINE
#define SCENE_SIMENGINE

#include "GLIncludes.h"
#include "GameObject.h"
#include "Vectors.h"

class Entity;

class Scene
{
public:
	Scene();

	void AddToScene(GameObject* inGameObject);
	void RemoveFromScene(GameObject* inGameObject);
	void Update(float inDT);

private:
	std::vector<GameObject*> mGameObjects;
};

#endif