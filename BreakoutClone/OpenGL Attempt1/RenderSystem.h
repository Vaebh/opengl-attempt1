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

	//const std::string GetSystemID();

	static RenderSystem* GetSingleton();

	void AddComponent(IRenderableComponent* inRenderableComponent);
	void RemoveComponent(IRenderableComponent* inRenderableComponent);
	void SetFrameBufferTarget(GLuint inFrameBuffer = 0);

	virtual void Update(float inDT);

	void Draw();

private:
	static RenderSystem* mRenderer;
	static GLFWwindow* mWindow;

	std::vector<IRenderableComponent*> mComponents;
};

#endif