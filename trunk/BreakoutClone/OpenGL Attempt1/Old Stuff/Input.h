#ifndef INPUT_SIMENGINE
#define INPUT_SIMENGINE

#include "GLIncludes.h"
#include "Entity.h"
#include <map>
#include <list>
#include "Command.h"

class Entity;
class Command;

class Input
{
public:
	Input(GLFWwindow* inWindow, Entity* inEntity);

	void Init();
	void InitKeys();

	void LoadInput();

	virtual void Update(const float inDT);

	// Prints out mouse coordinates
	static void mouseCallback(GLFWwindow * window, int button, int action, int mods);

private:
	void AssignCommand(Command* inCommand, const std::string inCommandName, const std::string inCommandKey);
	void ParseCommand(const std::string inCommandName, const std::string inCommandKey);

	void HandleKeyboardInput(const float inDT);
	void HandleKeyInput(const GLint inKey, const float inDT);

	void AddKey(const GLint inKeyCode);

private:
	GLFWwindow* mWindow;

	Entity* mEntity;

	std::vector<GLint> mKeys;
	std::map<std::string, int> mStringKeys;

	std::map<int, Command*> mCommandKeys;
};

#endif