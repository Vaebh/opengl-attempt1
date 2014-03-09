#include "Input.h"
#include "GLIncludes.h"

#include <fstream>

Input::Input(GLFWwindow* inWindow, Entity* inEntity) : window(inWindow), mEntity(inEntity)
{
	mStringKeys["W"] = GLFW_KEY_W;
	mStringKeys["A"] = GLFW_KEY_A;
	mStringKeys["S"] = GLFW_KEY_S;
	mStringKeys["D"] = GLFW_KEY_D;

	InitKeys();
}

void Input::InitKeys()
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
		mCommands[mStringKeys[inCommandKey]] = new MoveUpCommand();
	}

	if(inCommandName == "MoveLeft")
	{
		mCommands[mStringKeys[inCommandKey]] = new MoveLeftCommand();
	}

	if(inCommandName == "MoveDown")
	{
		mCommands[mStringKeys[inCommandKey]] = new MoveDownCommand();
	}

	if(inCommandName == "MoveRight")
	{
		mCommands[mStringKeys[inCommandKey]] = new MoveRightCommand();
	}
}

void Input::Update(float dt)
{
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mCommands[GLFW_KEY_W]->Execute(mEntity);
	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mCommands[GLFW_KEY_A]->Execute(mEntity);
	}

	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mCommands[GLFW_KEY_S]->Execute(mEntity);
	}

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mCommands[GLFW_KEY_D]->Execute(mEntity);
	}

	/*if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mKitten->moveX += 0.0001f;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mKitten->moveX -= 0.0001f;

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mKitten->moveY += 0.0001f;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mKitten->moveY -= 0.0001f;*/
}