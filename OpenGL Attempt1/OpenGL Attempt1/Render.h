#include "GLIncludes.h"
#include "Entity.h"
#include <vector>

class Render
{
public:
	Render();
	~Render();

	void AddEntity(Entity* inEntity);
	void SetFrameBufferTarget(GLuint inFrameBuffer = 0);

private:
	void Draw();
	std::vector<Entity*> mEntities;
};