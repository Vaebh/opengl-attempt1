#ifndef INPUT_MANAGER_SIMENGINE
#define INPUT_MANAGER_SIMENGINE

#include "GLIncludes.h"
#include <map>
#include <list>
#include "EventMessenger.h"
#include "Foundation.h"

class InputManager
{
public:
	InputManager(GLFWwindow* inWindow);

	void Init();
	void InitKeys();

	virtual void Update(const float inDT);

	// Prints out mouse coordinates
	static void mouseCallback(GLFWwindow * window, int button, int action, int mods);

private:
	void HandleKeyboardInput(const float inDT);
	void HandleKeyInput(const GLint inKey, const float inDT);

	void AddKey(const GLint inKeyCode, const uint32_t inEventType);

private:
	GLFWwindow* mWindow;
	GLint mPreviousKeyState;
	uint32_t mPreviousEvent;

	std::vector<GLint> mKeys;
	//replace vector with pair
	std::map<GLint, std::vector<uint32_t>> mInputMap;
};

#endif