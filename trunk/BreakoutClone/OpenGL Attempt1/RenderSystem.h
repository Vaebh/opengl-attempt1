#ifndef RENDERSYSTEM_SIMENGINE
#define RENDERSYSTEM_SIMENGINE

#include "GLIncludes.h"
#include "RenderableComponent.h"
#include "System.h"
#include <vector>

class RenderSystem : public ISystem
{
public:
	RenderSystem();
	~RenderSystem();

	static RenderSystem* GetSingleton();

	void AddComponent(IRenderableComponent* inRenderableComponent);
	void RemoveEntity(IRenderableComponent* inRenderableComponent);
	void SetFrameBufferTarget(GLuint inFrameBuffer = 0);

	void Draw();

private:
	static RenderSystem* mRenderer;
	static GLFWwindow* mWindow;

	std::vector<IRenderableComponent*> mEntities;
};

#endif