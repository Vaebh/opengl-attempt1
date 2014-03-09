#ifndef COMMAND_SIMENGINE
#define COMMAND_SIMENGINE

#include "Entity.h"

class Command
{
public:
	virtual void Execute(Entity* inEntity) = 0;
};

class MoveUpCommand : public Command
{
	void Execute(Entity* inEntity);
};

class MoveLeftCommand : public Command
{
	void Execute(Entity* inEntity);
};

class MoveDownCommand : public Command
{
	void Execute(Entity* inEntity);
};

class MoveRightCommand : public Command
{
	void Execute(Entity* inEntity);
};

#endif