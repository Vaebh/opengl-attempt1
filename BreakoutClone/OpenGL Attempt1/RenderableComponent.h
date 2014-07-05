#ifndef RENDERABLECOMPONENT_SIMENGINE
#define RENDERABLECOMPONENT_SIMENGINE

#include "Component.h"
#include "Shader.h"

class IRenderableComponent : public IComponent
{
public:
	IRenderableComponent();
	~IRenderableComponent();

	inline Shader* GetShader() const {return mShader;}
	inline bool IsVisible() const {return mVisible;}

	virtual void Update(float inDT) = 0;
	virtual void Draw() = 0;

	virtual void OnAttached(GameObject* inGameObject);

protected:
	Shader* mShader;
	bool mVisible;
};

#endif