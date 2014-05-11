#ifndef SCENE_SIMENGINE
#define SCENE_SIMENGINE

#include "GLIncludes.h"
#include "Entity.h"
#include "Vectors.h"
#include "Rectangle.h"

class Entity;

class Scene
{
public:
	Scene();

	bool IsColliding(Rectangle inBoundingBox, Entity* inEntity);

	void AddToScene(Entity* inEntity);
	void Update(float inDT);

private:
	bool IsIntersecting(Rectangle inA, Rectangle inB);

private:
	std::vector<Entity*> mEntities;
};

#endif