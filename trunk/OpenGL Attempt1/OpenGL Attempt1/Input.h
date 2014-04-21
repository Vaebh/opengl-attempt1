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

	virtual void Update(float dt);

	// Prints out mouse coordinates
	static void mouseCallback(GLFWwindow * window, int button, int action, int mods);

	// Keyboard controls, exit with Esc
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	static std::map<int, Command*> mCommandKeys;

private:

	GLFWwindow* mWindow;

	std::map<std::string, int> mStringKeys;
	std::vector<GLint> mKeys;

	void AssignCommand(Command* inCommand, std::string inCommandName, std::string inCommandKey);

private:
	
	void ParseCommand(std::string inCommandName, std::string inCommandKey);

	void HandleKeyboardInput(const float inDeltaTime) const;
	void HandleKeyInput(const GLint inKey, const float inDeltaTime) const;

	void AddKey(const GLint inKeyCode);

	static Entity* mEntity;
	static std::list<Command*> mCommands;
};

#endif