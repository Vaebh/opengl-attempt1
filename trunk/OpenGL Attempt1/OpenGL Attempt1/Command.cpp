#include "Command.h"

Command::Command() : mRepeatingAction(false), mInputState(0), mModifiers(0), mFinished(true), mSpeed(0.5f)
{

}

void MoveUpCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	//if(mInputState == GLFW_PRESS || mInputState == GLFW_REPEAT)
	//{
		inEntity->y += mSpeed * inDeltaTime;
	/*}
	else
	{
		mFinished = true;
	}*/
}

void MoveLeftCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->x -= mSpeed * inDeltaTime;
}

void MoveDownCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->y -= mSpeed * inDeltaTime;
}

void MoveRightCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->x += mSpeed * inDeltaTime;
}

ScaleCommand::ScaleCommand(Axis inAxis, int inDirection) : mAxis(inAxis), mDirection(inDirection)
{

}

void ScaleCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	if(mAxis == VERTICAL)
	{
		inEntity->scaleY += mDirection * 2 * inDeltaTime;
	}
	else
	{
		inEntity->scaleX += mDirection * 2 * inDeltaTime;
	}
}