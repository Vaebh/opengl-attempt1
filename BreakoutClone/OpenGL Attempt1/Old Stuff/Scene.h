#ifndef SCENE_SIMENGINE
#define SCENE_SIMENGINE

#include "GLIncludes.h"
#include "Entity.h"
#include "Vectors.h"

class Entity;

class Scene
{
public:
	Scene();

	void AddToScene(Entity* inEntity);
	void RemoveFromScene(Entity* inEntity);
	void Update(float inDT);

private:
	std::vector<Entity*> mEntitys;
};

#endif