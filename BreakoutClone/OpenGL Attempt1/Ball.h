#include "Sprite.h"

class Ball : public Sprite
{
public:
	Ball();
	~Ball();

	virtual void OnCollision();
	virtual void Update(float inDT);

	float mSpeed;
};