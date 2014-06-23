#ifndef RENDERABLECOMPONENT_SIMENGINE
#define RENDERABLECOMPONENT_SIMENGINE

#include "Component.h"
#include "Shader.h"

class IRenderableComponent : public IComponent
{
public:
	IRenderableComponent();
	~IRenderableComponent();

	void Update(float inDT) = 0;
	void Draw() = 0;

protected:
	Shader* mShader;
};

#endif