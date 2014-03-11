#include "Input.h"
#include "GLIncludes.h"

#include <fstream>

Entity* Input::mEntity;
std::map<int, Command*> Input::mCommandKeys;

Input::Input(GLFWwindow* inWindow, Entity* inEntity) : window(inWindow)
{
	glfwSetKeyCallback(window, key_callback);

	InitKeys();
	LoadKeys();

	mEntity = inEntity;
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(glfwGetKey(window, key) == GLFW_PRESS)
	{
		if(mCommandKeys[key])
		{
			mCommands[key]->Execute(mEntity);
		}
	}
}

void Input::InitKeys()
{
	mStringKeys["W"] = GLFW_KEY_W;
	mStringKeys["A"] = GLFW_KEY_A;
	mStringKeys["S"] = GLFW_KEY_S;
	mStringKeys["D"] = GLFW_KEY_D;
}

void Input::LoadKeys()
{
	std::string currentLine = "";
	std::ifstream inputFile;

	inputFile.open("Input.txt");
	while(inputFile.is_open() && !inputFile.bad() && !inputFile.eof())
	{
		getline(inputFile, currentLine);
		std::string::size_type delimiterIndex = currentLine.find(":");
		if(delimiterIndex != std::string::npos)
		{
			std::string commandName = currentLine.substr(0, delimiterIndex);
			std::string commandKey = currentLine.substr((delimiterIndex != currentLine.length()) ? delimiterIndex + 1 : 0, currentLine.length());
			//std::string repeatingAction =  currentLine.substr((delimiterIndex != currentLine.length()) ? delimiterIndex + 1 : 0, currentLine.length());

			ParseCommand(commandName, commandKey);
		}
	}
}

void Input::ParseCommand(std::string inCommandName, std::string inCommandKey)
{
	if(inCommandName == "")
	{
		return;
	}

	if(inCommandName == "MoveUp")
	{
		mCommandKeys[mStringKeys[inCommandKey]] = new MoveUpCommand();
	}

	if(inCommandName == "MoveLeft")
	{
		mCommandKeys[mStringKeys[inCommandKey]] = new MoveLeftCommand();
	}

	if(inCommandName == "MoveDown")
	{
		mCommandKeys[mStringKeys[inCommandKey]] = new MoveDownCommand();
	}

	if(inCommandName == "MoveRight")
	{
		mCommandKeys[mStringKeys[inCommandKey]] = new MoveRightCommand();
	}
}

void Input::Update(float dt)
{
	/*if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if(mCommands[GLFW_KEY_W])
		{
			mCommands[GLFW_KEY_W]->Execute(mEntity);
		}
	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if(mCommands[GLFW_KEY_A])
		{
			mCommands[GLFW_KEY_A]->Execute(mEntity);
		}
	}

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mCommands[GLFW_KEY_S]->Execute(mEntity);
	}

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mCommands[GLFW_KEY_D]->Execute(mEntity);
	}*/

	/*if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mKitten->moveX += 0.0001f;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mKitten->moveX -= 0.0001f;

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mKitten->moveY += 0.0001f;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mKitten->moveY -= 0.0001f;*/
}