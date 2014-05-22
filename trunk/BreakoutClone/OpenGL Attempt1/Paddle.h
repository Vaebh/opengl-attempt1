#include "Sprite.h"
#include "Ball.h"

class Paddle : public Sprite
{
public:
	Paddle(Ball* inBall);

	void LaunchBall();

	void Update(float inDT);

private:
	Ball* mBall;
};