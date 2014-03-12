#ifndef INPUT
#define INPUT

#include "GLIncludes.h"
#include "Sprite.h"
#include <map>
#include <list>
#include "Command.h"

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

	Sprite* mKitten;
	
	static std::map<int, Command*> mCommandKeys;

private:
	GLFWwindow* window;

	std::map<std::string, int> mStringKeys;

	void ParseCommand(std::string inCommandName, std::string inCommandKey);

	static Entity* mEntity;
  list<Command*> mCommands;
};

#endif