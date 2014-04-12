
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

	float x, y;
	float scaleX, scaleY;

private:

	bool mbVisible;
	std::string mName;
};
#endif