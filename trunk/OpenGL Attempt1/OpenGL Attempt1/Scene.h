#include "GLIncludes.h"
#include "Entity.h"
#include "Vectors.h"

class Scene
{
public:
	Scene();

	void AddToScene(Entity* inEntity);
	void Update(float inDT);

private:
	std::vector<Entity*> mEntities;
};