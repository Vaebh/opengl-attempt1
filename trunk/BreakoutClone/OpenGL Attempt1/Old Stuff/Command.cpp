#include "Command.h"
#include "Paddle.h"

Command::Command(std::string inName, std::string inKey) : mRepeatingAction(false), mInputState(0), mModifiers(0), mFinished(true), mSpeed(0.5f), mName(inName), mKey(inKey)
{

}

ReloadInputCommand::ReloadInputCommand(std::string inName, std::string inKey) : Command(inName, inKey)
{

}

void ReloadInputCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->mInput->LoadInput();
}

MoveCommand::MoveCommand(std::string inName, std::string inKey, Vector3 inDirection, float inSpeed) : Command(inName, inKey), mDirection(inDirection), mSpeed(inSpeed)
{

}

void MoveCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->MovePosition(mSpeed * inDeltaTime * mDirection);
}

ScaleCommand::ScaleCommand(std::string inName, std::string inKey, Vector3 inDirection) : Command(inName, inKey), mDirection(inDirection)
{

}

void ScaleCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->mScale += mDirection * inDeltaTime;
}

RotationCommand::RotationCommand(std::string inName, std::string inKey, Vector3 inAxis, float inSpeed) : Command(inName, inKey), mAxis(inAxis), mSpeed(inSpeed)
{

}

void RotationCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->mRotationAngle += mAxis * mSpeed * inDeltaTime;
}

LaunchBallCommand::LaunchBallCommand(std::string inName, std::string inKey) : Command(inName, inKey)
{

}

void LaunchBallCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	Paddle* thePaddle = dynamic_cast<Paddle*>(inEntity);
	if(thePaddle)
	{
		thePaddle->LaunchBall();
	}
}