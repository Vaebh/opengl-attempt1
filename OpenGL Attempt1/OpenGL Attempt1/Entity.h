
#ifndef ENTITY
#define ENTITY

#include "GLIncludes.h"
#include <vector>

class Entity
{
public:
	Entity();
	~Entity();

	virtual void Draw();

	inline bool IsVisible() const {return mbVisible;}
	inline void SetVisible(bool inbVisible) {mbVisible = inbVisible;}

private:

	bool mbVisible;
};
#endif