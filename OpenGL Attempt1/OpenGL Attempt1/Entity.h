
#ifndef ENTITY
#define ENTITY

#include "GLIncludes.h"
#include "Vectors.h"
#include <vector>

class Entity
{
public:
	Entity();
	~Entity();

	virtual void Draw();

	inline bool IsVisible() const {return mbVisible;}
	inline void SetVisible(bool inbVisible) {mbVisible = inbVisible;}

	inline Vector3 GetPosition() {return mPosition;}
	inline void SetPosition(Vector3 inPosition) {mPosition = inPosition;}

	inline void MovePosition(Vector3 inMovement) {mPosition += inMovement;}

	Vector3 mScale;

protected:
	Vector3 mPosition;

private:

	bool mbVisible;
	std::string mName;
};
#endif