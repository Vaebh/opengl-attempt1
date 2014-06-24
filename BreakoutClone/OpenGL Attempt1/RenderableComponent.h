#ifndef RENDERABLECOMPONENT_SIMENGINE
#define RENDERABLECOMPONENT_SIMENGINE

#include "Component.h"
#include "Shader.h"

class IRenderableComponent : public IComponent
{
public:
	//IRenderableComponent();
	//~IRenderableComponent();

	inline Shader* GetShader() const {return mShader;}

	virtual void Update(float inDT) = 0;
	virtual void Draw() = 0;

protected:
	Shader* mShader;
};

#endif