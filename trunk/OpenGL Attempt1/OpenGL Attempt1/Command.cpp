#include "Command.h"

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