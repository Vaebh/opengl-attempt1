#include "BreakoutFactory.h"
#include "AnimatedSpriteComponent.h"
#include "RenderSystem.h"

GameObject* CreateBall()
{
	GameObject* theBall = new GameObject();

	AnimatedSpriteComponent* sprite = new AnimatedSpriteComponent("ball2.png", 2);
	RenderSystem::GetSingleton()->AddComponent(sprite);

	theBall->Attach(sprite);

	return theBall;
}