#ifndef RENDER_SIMENGINE
#define RENDER_SIMENGINE

#include "GLIncludes.h"
#include "Entity.h"
#include <vector>

class Render
{
public:
	Render();
	~Render();

	static Render* GetSingleton();

	void AddEntity(Entity* inEntity);
	void RemoveEntity(Entity* inEntity);
	void SetFrameBufferTarget(GLuint inFrameBuffer = 0);

	void Draw();

	static Render* mRenderer;

private:
	std::vector<Entity*> mEntities;
};

#endif