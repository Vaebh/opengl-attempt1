#ifndef ENTITY_SIMENGINE
#define ENTITY_SIMENGINE

#include "GLIncludes.h"
#include "Vectors.h"
#include <vector>
#include "Input.h"
#include "Scene.h"
#include "Rectangle.h"
#include "Shader.h"

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

	void ScaleBy(Vector3 inScale) {mScale += inScale;}

	inline void SetOwningScene(Scene* inScene) {mScene = inScene;}

	virtual void OnCollision(Entity* inEntity, Vector3& inCollisionVector, Rectangle inSimulatedBoundingBox);

	virtual glm::mat4 CalculateMatrix() = 0;

	Rectangle mBoundingBox;

	Vector3 mScale;
	Vector3 mRotationAngle;

	virtual void Update(float inDT);

	Input* mInput;

	Rectangle CreateBoundingBox(Vector3 inPosition);

	Shader* mShader;

	bool mCollidable;

protected:
	Vector3 mPosition;

	std::string mName;

private:
	bool mbVisible;

	Scene* mScene;
};
#endif