#ifndef COMMAND_SIMENGINE
#define COMMAND_SIMENGINE

#include "Entity.h"
#include "Vectors.h"

class Input;
class Entity;

class Command
{
public:
	Command(std::string inName, std::string inKey);
	virtual void Execute(Entity* inEntity, float inDeltaTime) = 0;
   
public:
	bool mRepeatingAction;
	int mInputState;
	int mModifiers;
	bool mFinished;
	float mSpeed;

	std::string mName;
	std::string mKey;
};

class ReloadInputCommand : public Command
{
public:
	ReloadInputCommand(std::string inName, std::string inKey);
	void Execute(Entity* inEntity, float inDeltaTime);
};

class MoveCommand : public Command
{
public:
	MoveCommand(std::string inName, std::string inKey, Vector3 inDirection, float inSpeed);
	~MoveCommand();
	virtual void Execute(Entity* inEntity, float inDeltaTime);
  
protected:
	float mSpeed;
	Vector3 mDirection;
};

class ScaleCommand : public Command
{
public:
	ScaleCommand(std::string inName, std::string inKey, Vector3 inDirection);
	void Execute(Entity* inEntity, float inDeltaTime);

private:
	Vector3 mDirection;
};

#endif

