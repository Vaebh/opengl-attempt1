#ifndef SYSTEM_SIMENGINE
#define SYSTEM_SIMENGINE

#include "Component.h"
#include <string>
#include <vector>

class ISystem
{
public:
	ISystem();
	virtual ~ISystem();

	void Update(float inDT);

	virtual std::string GetSystemID() = 0;

private:
	std::vector<IComponent*> mComponents;
};

#endif