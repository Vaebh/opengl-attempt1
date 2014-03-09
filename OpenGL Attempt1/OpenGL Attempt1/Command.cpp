#include "Command.h"

void MoveUpCommand::Execute(Entity* inEntity)
{
	inEntity->y += 0.0001f;
}

void MoveLeftCommand::Execute(Entity* inEntity)
{
	inEntity->x -= 0.0001f;
}

void MoveDownCommand::Execute(Entity* inEntity)
{
	inEntity->y -= 0.0001f;
}

void MoveRightCommand::Execute(Entity* inEntity)
{
	inEntity->x += 0.0001f;
}