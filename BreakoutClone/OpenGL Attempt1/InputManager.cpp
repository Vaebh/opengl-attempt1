#include "InputManager.h"
#include <string>

#include <fstream>
#include <iostream>

InputManager::InputManager(GLFWwindow* inWindow) :
mWindow(inWindow)
,mPreviousEvent(0)
,mPreviousKeyState(0)
{
	Init();
	//LoadInput();
}

void InputManager::Init()
{
	InitKeys();
}

void InputManager::InitKeys()
{
	/*AddKey(GLFW_KEY_1);
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

	AddKey(GLFW_KEY_Q);*/
	AddKey(GLFW_KEY_W, INPUT_W_PRESS);
	/*AddKey(GLFW_KEY_E);
	AddKey(GLFW_KEY_R);

	AddKey(GLFW_KEY_T);
	AddKey(GLFW_KEY_Y);
	AddKey(GLFW_KEY_U);
	AddKey(GLFW_KEY_I);

	AddKey(GLFW_KEY_O);
	AddKey(GLFW_KEY_P);
	AddKey(GLFW_KEY_LEFT_BRACKET);
	AddKey(GLFW_KEY_RIGHT_BRACKET);
	AddKey(GLFW_KEY_ENTER);*/

	AddKey(GLFW_KEY_A, INPUT_A_PRESS);
	AddKey(GLFW_KEY_S, INPUT_S_PRESS);
	AddKey(GLFW_KEY_D, INPUT_D_PRESS);
	/*AddKey(GLFW_KEY_F);

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
	AddKey(GLFW_KEY_LEFT_ALT);*/
	AddKey(GLFW_KEY_SPACE, INPUT_SPACE_PRESS);
	AddKey(GLFW_KEY_SPACE, INPUT_SPACE_RELEASE);
	/*AddKey(GLFW_KEY_RIGHT_ALT);
	AddKey(GLFW_KEY_RIGHT_CONTROL);

	AddKey(GLFW_KEY_LEFT);
	AddKey(GLFW_KEY_DOWN);
	AddKey(GLFW_KEY_RIGHT);
	AddKey(GLFW_KEY_UP);*/
}

void InputManager::AddKey(const GLint inKeyCode, uint32_t inEventType)
{
	mKeys.push_back(inKeyCode);
	mInputMap[inKeyCode].push_back(inEventType);
}

void InputManager::HandleKeyInput(const GLint inKey, const float inDT)
{
	int keyInputState = glfwGetKey(mWindow, inKey);

	if((keyInputState == GLFW_PRESS && mPreviousKeyState != GLFW_PRESS) ||
		keyInputState == GLFW_RELEASE && mPreviousKeyState != GLFW_RELEASE)
	{
		for(uint32_t i = 0; i < mInputMap[inKey].size(); ++i)
		{
			if(mInputMap[inKey][i] != mPreviousEvent)
			{
				if((keyInputState == GLFW_PRESS && i == 0) ||
					(keyInputState == GLFW_RELEASE && i == 1))
				{
					EventMessenger::GetSingleton()->BroadcastEvent(mInputMap[inKey][i]);
					mPreviousEvent = mInputMap[inKey][i];
					mPreviousKeyState = keyInputState;
					break;
				}
			}
		}
	}



	/*if(keyInputState == GLFW_PRESS || (keyInputState == GLFW_RELEASE && mPreviousKeyState == GLFW_PRESS))
	{
		for(uint32_t i = 0; i < mInputMap[inKey].size(); ++i)
		{
			if(mInputMap[inKey][i] != mPreviousEvent)
			{
				EventMessenger::GetSingleton()->BroadcastEvent(mInputMap[inKey][i]);
				mPreviousEvent = mInputMap[inKey][i];
				mPreviousKeyState = keyInputState;
				break;
			}
		}
	}*/
}

void InputManager::HandleKeyboardInput(const float inDT)
{
	for(int i = 0; i < mKeys.size(); ++i)
	{
		HandleKeyInput(mKeys[i], inDT);
	}
}

void InputManager::Update(const float inDT)
{
	HandleKeyboardInput(inDT);
}