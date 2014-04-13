#include "Command.h"
#include "Vectors.h"

Command::Command() : mRepeatingAction(false), mInputState(0), mModifiers(0), mFinished(true), mSpeed(0.5f)
{

}

void MoveUpCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	//if(mInputState == GLFW_PRESS || mInputState == GLFW_REPEAT)
	//{

	inEntity->MovePosition(Vector3(0.0, mSpeed * inDeltaTime, 0.0));
	/*}
	else
	{
		mFinished = true;
	}*/
}

void MoveLeftCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->MovePosition(-Vector3(mSpeed * inDeltaTime, 0.0, 0.0));
}

void MoveDownCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->MovePosition(-Vector3(0.0, mSpeed * inDeltaTime, 0.0));
}

void MoveRightCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->MovePosition(Vector3(mSpeed * inDeltaTime, 0.0, 0.0));
}

ScaleCommand::ScaleCommand(Axis inAxis, int inDirection) : mAxis(inAxis), mDirection(inDirection)
{

}

void ScaleCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	if(mAxis == VERTICAL)
	{
		inEntity->mScale.y += mDirection * 2 * inDeltaTime;
	}
	else
	{
		inEntity->mScale.x += mDirection * 2 * inDeltaTime;
	}
}