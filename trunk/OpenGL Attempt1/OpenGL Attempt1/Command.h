#ifndef COMMAND_SIMENGINE
#define COMMAND_SIMENGINE

#include "Entity.h"

class Command
{
public:
  Command();
	virtual void Execute(Entity* inEntity, float inDeltaTime) = 0;
   
public:
  bool mRepeatingAction;
};

class MoveUpCommand : public Command
{
	void Execute(Entity* inEntity, float inDeltaTime);
};

class MoveLeftCommand : public Command
{
	void Execute(Entity* inEntity, float inDeltaTime);
};

class MoveDownCommand : public Command
{
	void Execute(Entity* inEntity, float inDeltaTime);
};

class MoveRightCommand : public Command
{
	void Execute(Entity* inEntity, float inDeltaTime);
};

#endif