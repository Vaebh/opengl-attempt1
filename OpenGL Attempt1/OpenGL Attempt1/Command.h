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
  int mInputState;
  int mModifiers;
  bool mFinished;
  float mSpeed;
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

class ScaleCommand : public Command
{
public:
	enum Axis
	{
		VERTICAL,
		HORIZONTAL
	};

	ScaleCommand(Axis inAxis, int inDirection);
	void Execute(Entity* inEntity, float inDeltaTime);

private:
	Axis mAxis;
	int mDirection;
};

#endif