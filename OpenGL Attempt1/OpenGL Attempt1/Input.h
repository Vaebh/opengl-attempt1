#include "GLIncludes.h"

class Input
{
public:
	// Prints out mouse coordinates
	static void mouseCallback(GLFWwindow * window, int button, int action, int mods);

	// Keyboard controls, exit with Esc
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}