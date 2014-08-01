#ifndef COMPONENT_BALL_CONTROLLER_SIMENGINE
#define COMPONENT_BALL_CONTROLLER_SIMENGINE

#include "../Structure/GameObject.h"
#include "../Game/ComponentBallModel.h"
#include "../Foundation/Foundation.h"

class ComponentBallController : public IComponent
{
public:
	ComponentBallController(ComponentBallModel* inBallModel);

	void Update(float inDT);

	void CheckForWindowCollision();

	void HandleEvent(uint32_t inEventType, GameObject* inTarget);

	void LaunchBall();

	void OnAttached(GameObject* inGameObject);

	inline void SetAimingObject(GameObject* inAimingObject) {mAimingObject = inAimingObject;}

	//void EnableAimMode();

private:
	ComponentBallModel* mBallModel;
	GameObject* mAimingObject;

	bool mAiming;
};

#endif