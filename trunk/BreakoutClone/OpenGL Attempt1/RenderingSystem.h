#ifndef RENDERINGSYSTEM_SIMENGINE
#define RENDERINGSYSTEM_SIMENGINE

#include "System.h"
#include <string>
#include <vector>

class ISystem
{
public:
	ISystem();
	virtual ~ISystem();

	void Update(float inDT);

	virtual std::string GetSystemID();

private:
	std::vector<IComponent*> mComponents;
};

#endif