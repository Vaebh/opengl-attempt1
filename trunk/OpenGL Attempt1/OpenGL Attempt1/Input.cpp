#include "Input.h"
#include <string>

#include <fstream>
#include <iostream>

Input::Input(GLFWwindow* inWindow, Entity* inEntity) : mWindow(inWindow), mEntity(inEntity)
{
	inEntity->mInput = this;

	Init();
	LoadInput();
}

void Input::Init()
{
	InitKeys();
}

void Input::InitKeys()
{
	AddKey(GLFW_KEY_1);
	AddKey(GLFW_KEY_2);
	AddKey(GLFW_KEY_3);
	AddKey(GLFW_KEY_4);

	AddKey(GLFW_KEY_5);
	AddKey(GLFW_KEY_6);
	AddKey(GLFW_KEY_7);
	AddKey(GLFW_KEY_8);

	AddKey(GLFW_KEY_9);
	AddKey(GLFW_KEY_MINUS);
	AddKey(GLFW_KEY_EQUAL);
	AddKey(GLFW_KEY_BACKSPACE);

	AddKey(GLFW_KEY_Q);
	AddKey(GLFW_KEY_W);
	AddKey(GLFW_KEY_E);
	AddKey(GLFW_KEY_R);

	AddKey(GLFW_KEY_T);
	AddKey(GLFW_KEY_Y);
	AddKey(GLFW_KEY_U);
	AddKey(GLFW_KEY_I);

	AddKey(GLFW_KEY_O);
	AddKey(GLFW_KEY_P);
	AddKey(GLFW_KEY_LEFT_BRACKET);
	AddKey(GLFW_KEY_RIGHT_BRACKET);
	AddKey(GLFW_KEY_ENTER);

	AddKey(GLFW_KEY_A);
	AddKey(GLFW_KEY_S);
	AddKey(GLFW_KEY_D);
	AddKey(GLFW_KEY_F);

	AddKey(GLFW_KEY_G);
	AddKey(GLFW_KEY_H);
	AddKey(GLFW_KEY_J);
	AddKey(GLFW_KEY_K);

	AddKey(GLFW_KEY_L);
	AddKey(GLFW_KEY_SEMICOLON);
	AddKey(GLFW_KEY_APOSTROPHE);

	AddKey(GLFW_KEY_LEFT_SHIFT);
	AddKey(GLFW_KEY_BACKSLASH);
	AddKey(GLFW_KEY_Z);
	AddKey(GLFW_KEY_X);
	AddKey(GLFW_KEY_C);

	AddKey(GLFW_KEY_V);
	AddKey(GLFW_KEY_B);
	AddKey(GLFW_KEY_N);
	AddKey(GLFW_KEY_M);

	AddKey(GLFW_KEY_COMMA);
	AddKey(GLFW_KEY_PERIOD);
	AddKey(GLFW_KEY_SLASH);
	AddKey(GLFW_KEY_RIGHT_SHIFT);

	AddKey(GLFW_KEY_LEFT_CONTROL);
	AddKey(GLFW_KEY_LEFT_ALT);
	AddKey(GLFW_KEY_SPACE);
	AddKey(GLFW_KEY_RIGHT_ALT);
	AddKey(GLFW_KEY_RIGHT_CONTROL);

	AddKey(GLFW_KEY_LEFT);
	AddKey(GLFW_KEY_DOWN);
	AddKey(GLFW_KEY_RIGHT);
	AddKey(GLFW_KEY_UP);
}

void Input::AddKey(const GLint inKeyCode)
{
	mKeys.push_back(inKeyCode);
  

	// Non single character keys
	if(inKeyCode == GLFW_KEY_SPACE)
	{
		mStringKeys["Space"] = GLFW_KEY_SPACE;
	}
	else if(inKeyCode == GLFW_KEY_BACKSPACE)
	{
		mStringKeys["Backspace"] = GLFW_KEY_BACKSPACE;
	}
	else if(inKeyCode == GLFW_KEY_ENTER)
	{
		mStringKeys["Enter"] = GLFW_KEY_ENTER;
	}
	else if(inKeyCode == GLFW_KEY_LEFT_SHIFT)
	{
		mStringKeys["LShift"] = GLFW_KEY_LEFT_SHIFT;
	}
	else if(inKeyCode == GLFW_KEY_RIGHT_SHIFT)
	{
		mStringKeys["RShift"] = GLFW_KEY_RIGHT_SHIFT;
	}
	else if(inKeyCode == GLFW_KEY_LEFT_CONTROL)
	{
		mStringKeys["LCtrl"] = GLFW_KEY_LEFT_CONTROL;
	}
	else if(inKeyCode == GLFW_KEY_RIGHT_CONTROL)
	{
		mStringKeys["RCtrl"] = GLFW_KEY_RIGHT_CONTROL;
	}
	else if(inKeyCode == GLFW_KEY_LEFT_ALT)
	{
		mStringKeys["LAlt"] = GLFW_KEY_LEFT_ALT;
	}
	else if(inKeyCode == GLFW_KEY_RIGHT_ALT)
	{
		mStringKeys["RAlt"] = GLFW_KEY_RIGHT_ALT;
	}
	else if(inKeyCode == GLFW_KEY_LEFT)
	{
		mStringKeys["Left"] = GLFW_KEY_LEFT;
	}
	else if(inKeyCode == GLFW_KEY_DOWN)
	{
		mStringKeys["Down"] = GLFW_KEY_DOWN;
	}
	else if(inKeyCode == GLFW_KEY_RIGHT)
	{
		mStringKeys["Right"] = GLFW_KEY_RIGHT;
	}
	else if(inKeyCode == GLFW_KEY_UP)
	{
		mStringKeys["Up"] = GLFW_KEY_UP;
	}
	else
	{
		std::string keyString(1, (char)inKeyCode);

		mStringKeys[keyString] = inKeyCode;
	}
}

void Input::LoadInput()
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

void Input::ParseCommand(const std::string inCommandName, const std::string inCommandKey)
{
	if(inCommandName == "")
	{
		return;
	}

	Command* command = NULL;

	if(inCommandName == "MoveUp")
	{
		command = new MoveCommand("MoveUp", inCommandKey, Y_UNIT_POSITIVE, 0.5f);
	}

	if(inCommandName == "MoveLeft")
	{
		command = new MoveCommand("MoveLeft", inCommandKey, X_UNIT_NEGATIVE, 0.5f);
	}

	if(inCommandName == "MoveDown")
	{
		command = new MoveCommand("MoveDown", inCommandKey, Y_UNIT_NEGATIVE, 0.5f);
	}

	if(inCommandName == "MoveRight")
	{
		command = new MoveCommand("MoveRight", inCommandKey, X_UNIT_POSITIVE, 0.5f);
	}

	if(inCommandName == "ScaleBiggerX")
	{
		command = new ScaleCommand("ScaleBiggerX", inCommandKey, X_UNIT_POSITIVE);
	}

	if(inCommandName == "ScaleBiggerY")
	{
		command = new ScaleCommand("ScaleBiggerY", inCommandKey, Y_UNIT_POSITIVE);
	}

	if(inCommandName == "ScaleSmallerX")
	{
		command = new ScaleCommand("ScaleSmallerX", inCommandKey, X_UNIT_NEGATIVE);
	}

	if(inCommandName == "ScaleSmallerY")
	{
		command = new ScaleCommand("ScaleSmallerY", inCommandKey, Y_UNIT_NEGATIVE);
	}

	if(inCommandName == "RotateLeftZ")
	{
		command = new RotationCommand("RotateLeftZ", inCommandKey, Z_UNIT_POSITIVE, 50);
	}
	if(inCommandName == "RotateRightZ")
	{
		command = new RotationCommand("RotateRightZ", inCommandKey, Z_UNIT_NEGATIVE, 50);
	}

	if(inCommandName == "RotateUpY")
	{
		command = new RotationCommand("RotateUpY", inCommandKey, Y_UNIT_POSITIVE, 50);
	}
	if(inCommandName == "RotateDownY")
	{
		command = new RotationCommand("RotateDownY", inCommandKey, Y_UNIT_NEGATIVE, 50);
	}

	if(inCommandName == "RotateLeftX")
	{
		command = new RotationCommand("RotateLeftX", inCommandKey, X_UNIT_POSITIVE, 50);
	}
	if(inCommandName == "RotateRightX")
	{
		command = new RotationCommand("RotateRightX", inCommandKey, X_UNIT_NEGATIVE, 50);
	}

	if(inCommandName == "ReloadInput")
	{
		command = new ReloadInputCommand("ReloadInput", inCommandKey);
	}

	if(command)
	{
		AssignCommand(command, inCommandName, inCommandKey);
	}
}

void Input::AssignCommand(Command* inCommand, const std::string inCommandName, const std::string inCommandKey)
{
	if(mCommandKeys[mStringKeys[inCommandName]] != NULL)
	{
		delete mCommandKeys[mStringKeys[inCommandName]];
		mCommandKeys[mStringKeys[inCommandName]] = NULL;
	}

	// Assign the command to the correct keyboard key
	mCommandKeys[mStringKeys[inCommandKey]] = inCommand;

	// Make the name of the command into a mapKey that points at the keyboard key
	// This is so we can look up the command with its name
	mStringKeys[inCommandName] = mStringKeys[inCommandKey];
}

void Input::HandleKeyInput(const GLint inKey, const float inDT)
{
	int keyInputState = glfwGetKey(mWindow, inKey);
	if(keyInputState == GLFW_PRESS)
	{
		if(mCommandKeys[inKey])
		{
			mCommandKeys[inKey]->mInputState = keyInputState;
			mCommandKeys[inKey]->Execute(mEntity, inDT);
		}
	}
}

void Input::HandleKeyboardInput(const float inDT)
{
	for(int i = 0; i < mKeys.size(); ++i)
	{
		HandleKeyInput(mKeys[i], inDT);
	}
}

void Input::Update(const float inDT)
{
	HandleKeyboardInput(inDT);
}