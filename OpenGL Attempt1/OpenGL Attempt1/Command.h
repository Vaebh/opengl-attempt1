#ifndef COMMAND_SIMENGINE
#define COMMAND_SIMENGINE

#include "Entity.h"

class Command
{
public:
  Command(bool inOnceOff);
	virtual void Execute(Entity* inEntity, float inDeltaTime) = 0;
   
public:
  bool mRepeatingAction;
  int mInputState;
  int mModifiers;
  bool mFinished;
};

class MoveCommand : public Command
{
public:
  MoveCommand();
  ~MoveCommand();
  virtual void Execute(Entity* inEntity, float inDeltaTime) = 0;
  
protected:
  float mSpeed;
};

class MoveUpCommand : public MoveCommand
{
	void Execute(Entity* inEntity, float inDeltaTime);
};

class MoveLeftCommand : public MoveCommand
{
	void Execute(Entity* inEntity, float inDeltaTime);
};

class MoveDownCommand : public MoveCommand
{
	void Execute(Entity* inEntity, float inDeltaTime);
};

class MoveRightCommand : public MoveCommand
{
	void Execute(Entity* inEntity, float inDeltaTime);
};

#endif