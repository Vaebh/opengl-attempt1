#ifndef ENTITY_SIMENGINE
#define ENTITY_SIMENGINE

#include "GLIncludes.h"
#include "Vectors.h"
#include <vector>
#include "Input.h"
#include "Scene.h"
#include "Rectangle.h"

class Input;
class Scene;

class Entity
{
public:
	Entity();
	~Entity();

	virtual void Draw();

	inline bool IsVisible() const {return mbVisible;}
	inline void SetVisible(bool inbVisible) {mbVisible = inbVisible;}

	const inline Vector3 GetPosition() const {return mPosition;}
	inline void SetPosition(Vector3 inPosition) {mPosition = inPosition;}

	void MovePosition(Vector3 inMovement);

	inline void SetOwningScene(Scene* inScene) {mScene = inScene;}

	Rectangle mBoundingBox;

	Vector3 mScale;
	Vector3 mRotationAngle;

	virtual void Update(float inDeltaTime);

	Input* mInput;

	Rectangle CreateBoundingBox(Vector3 inPosition);

protected:
	Vector3 mPosition;

private:
	bool mbVisible;
	std::string mName;

	Scene* mScene;
};
#endif