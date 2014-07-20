#include "ComponentBallController.h"
#include "RenderSystem.h"
#include "EventMessenger.h"

ComponentBallController::ComponentBallController(ComponentBallModel* inBallModel) : 
IComponent(),
mBallModel(inBallModel)
{
	assert(mBallModel);
}

void ComponentBallController::HandleEvent(uint32_t inEventType, GameObject* inTarget)
{
	if(inEventType == INPUT_SPACE_PRESS)
	{
		LaunchBall();
	}
}

void ComponentBallController::OnAttached(GameObject* inGameObject)
{
	IComponent::OnAttached(inGameObject);

	IEventCallback* newCallbackMember = new EventCallbackMember<ComponentBallController>(this, &ComponentBallController::HandleEvent);
	EventMessenger::GetSingleton()->SubscribeToEvent(INPUT_SPACE_PRESS, mOwner, newCallbackMember);
}

void ComponentBallController::LaunchBall()
{
	if(!mBallModel->IsMovementEnabled())
	{
		// TODO - Hold this as part of the models construction
		mOwner->mVelocity = Vector3(0.f, 0.9f, 0.f);

		mBallModel->EnableMovement(true);
	}
}

void ComponentBallController::CheckForWindowCollision()
{
	if(mOwner->GetPosition().y >= 0.95f)
	{
		mOwner->mVelocity.y *= mOwner->mVelocity.y < 0 ? 1 : -1;
	}

	if(mOwner->GetPosition().x >= 0.95f)
	{
		mOwner->mVelocity.x *= mOwner->mVelocity.x < 0 ? 1 : -1;
	}

	if(mOwner->GetPosition().x <= -0.95f)
	{
		mOwner->mVelocity.x *= mOwner->mVelocity.x > 0 ? 1 : -1;
	}
}

void ComponentBallController::Update(float inDT)
{
	CheckForWindowCollision();

	if(mBallModel->IsMovementEnabled() && (mOwner->GetPosition().y <= -1.2f || glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_C)))
	{
		mOwner->mVelocity = Vector3();
		mBallModel->EnableMovement(false);
		mOwner->SetPosition(mBallModel->GetInitialPosition());
	}
}