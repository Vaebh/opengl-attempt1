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
	AddKey(GLFW_KEY_W, INPUT_W_PRESS, INPUT_W_RELEASE);
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

	AddKey(GLFW_KEY_A, INPUT_A_PRESS, INPUT_A_RELEASE);
	AddKey(GLFW_KEY_S, INPUT_S_PRESS, INPUT_S_RELEASE);
	AddKey(GLFW_KEY_D, INPUT_D_PRESS, INPUT_D_RELEASE);
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
	AddKey(GLFW_KEY_SPACE, INPUT_SPACE_PRESS, INPUT_SPACE_RELEASE);
	/*AddKey(GLFW_KEY_RIGHT_ALT);
	AddKey(GLFW_KEY_RIGHT_CONTROL);

	AddKey(GLFW_KEY_LEFT);
	AddKey(GLFW_KEY_DOWN);
	AddKey(GLFW_KEY_RIGHT);
	AddKey(GLFW_KEY_UP);*/
}

void InputManager::AddKey(const GLint inKeyCode, const uint32_t inPressedEventType, const uint32_t inReleasedEventType)
{
	Key theKey;
	theKey.mKeyCode = inKeyCode;
	theKey.mPreviousState = GLFW_RELEASE;
	mKeys.push_back(theKey);

	mInputMap[inKeyCode].first = inPressedEventType;
	mInputMap[inKeyCode].second = inReleasedEventType;
}

void InputManager::HandleKeyInput(Key& inKey, const float inDT)
{
	int keyInputState = glfwGetKey(mWindow, inKey.mKeyCode);

	if((keyInputState == GLFW_PRESS && inKey.mPreviousState != GLFW_PRESS) ||
		keyInputState == GLFW_RELEASE && inKey.mPreviousState != GLFW_RELEASE)
	{
		if(keyInputState == GLFW_PRESS && mPreviousEvent != mInputMap[inKey.mKeyCode].first)
		{
			EventMessenger::GetSingleton()->BroadcastEvent(mInputMap[inKey.mKeyCode].first);
			mPreviousEvent = mInputMap[inKey.mKeyCode].first;
			inKey.mPreviousState = keyInputState;
		}
		else if(keyInputState == GLFW_RELEASE && mPreviousEvent != mInputMap[inKey.mKeyCode].second)
		{
     		EventMessenger::GetSingleton()->BroadcastEvent(mInputMap[inKey.mKeyCode].second);
			mPreviousEvent = mInputMap[inKey.mKeyCode].second;
			inKey.mPreviousState = keyInputState;
		}
	}
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