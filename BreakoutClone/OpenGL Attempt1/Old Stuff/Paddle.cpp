#include "Paddle.h"
#include "Render.h"
#include <iostream>

Paddle::Paddle(Ball* inBall) : Sprite("paddle.png"),
mBall(inBall)
{
	SetPosition(Vector3(0, -0.89f, 0.f));
	mScale = Vector3(0.3, 0.17, 0);
}

void Paddle::LaunchBall()
{
	mBall->mMovementEnabled = true;
}

void Paddle::Update(float inDT)
{
	Sprite::Update(inDT);

	double mouseX, mouseY;

	glfwGetCursorPos(Render::mWindow, &mouseX, &mouseY);
	//std::cout << "XPos: " << mouseX << " YPos: " << mouseY << std::endl;

	/*int width, height;
	glfwGetFramebufferSize(Render::mWindow, &width, &height);

	float screenRatioW = (width / (float)height);
	float screenRatioH = (height / (float)width) * screenRatioW;

	mouseX = ((mouseX * (screenRatioW * 2)) / width) - screenRatioW;
	mouseY = ((mouseY * (screenRatioH * 2)) / height) - screenRatioH;*/

	//OldRange = (OldMax - OldMin)  
	//NewRange = (NewMax - NewMin)  
	//NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin

	int width, height;
	glfwGetFramebufferSize(Render::mWindow, &width, &height);

	float xPos = ((mouseX * 2) / width) - 1;

	//Vector3 pos = glm::ortho * glm::vec4(GetPosition().x, GetPosition().y, GetPosition().z, 1.f);

	SetPosition(Vector3(xPos, GetPosition().y, GetPosition().z));

	if(!mBall->mMovementEnabled)
	{
		Vector3 ballPosition = Vector3(GetPosition().x, GetPosition().y + mScale.y * 1.2f, GetPosition().z);
		mBall->SetPosition(ballPosition);
	}
}