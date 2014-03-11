#include "Command.h"

Command::Command() : mRepeatingAction(false)
{

}

void MoveUpCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->y += 0.1f * inDeltaTime;
}

void MoveLeftCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->x -= 0.1f * inDeltaTime;
}

void MoveDownCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->y -= 0.1f * inDeltaTime;
}

void MoveRightCommand::Execute(Entity* inEntity, float inDeltaTime)
{
	inEntity->x += 0.1f * inDeltaTime;
}