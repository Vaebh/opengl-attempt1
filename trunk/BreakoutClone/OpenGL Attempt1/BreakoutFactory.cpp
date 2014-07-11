#include "BreakoutFactory.h"
#include "AnimatedSpriteComponent.h"
#include "BounceComponent.h"
#include "RenderSystem.h"
#include "FollowMouseComponent.h"
#include "FragileCollisionComponent.h"

GameObject* CreateBall()
{
	GameObject* const theBall = new GameObject();
	theBall->SetPosition(Vector3(-0.2, -0.7, 0));
	theBall->mScale = Vector3(0.1, 0.1, 0);

	AnimatedSpriteComponent* const animSpriteComp = new AnimatedSpriteComponent("ball2.png", 2, 1.f, true);
	theBall->Attach(animSpriteComp);

	BounceComponent* const bounceComp = new BounceComponent(1.6f);
	theBall->Attach(bounceComp);

	theBall->mName = "Ball";

	return theBall;
}

GameObject* CreatePaddle()
{
	GameObject* const thePaddle = new GameObject();
	thePaddle->SetPosition(Vector3(0, -0.89f, 0.f));
	thePaddle->mScale = Vector3(0.3, 0.17, 0);

	SpriteComponent* const animSpriteComp = new SpriteComponent("paddle.png", 1);
	thePaddle->Attach(animSpriteComp);

	CollisionComponent* const collisionComp = new CollisionComponent();
	thePaddle->Attach(collisionComp);

	FollowMouseComponent* const followMouseComp = new FollowMouseComponent(X_AXIS);
	thePaddle->Attach(followMouseComp);

	thePaddle->mName = "Paddle";

	return thePaddle;
}

/*GameObject* CreateBlock()
{
	GameObject* const theBlock = new GameObject();

	theBlock->mScale = Vector3(0.2, 0.2, 0);

	SpriteComponent* const animSpriteComp = new SpriteComponent("bros.png", 1);
	theBlock->Attach(animSpriteComp);

	FragileCollisionComponent* const fragileColComp = new FragileCollisionComponent();
	theBlock->Attach(fragileColComp);

	return theBlock;
}*/