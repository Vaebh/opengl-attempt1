#ifndef COMMAND_SIMENGINE
#define COMMAND_SIMENGINE

#include "Entity.h"

class Command
{
public:
  Command();
	virtual void Execute(Entity* inEntity) = 0;
   
public:
  bool mRepeatingAction;
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