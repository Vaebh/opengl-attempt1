#include "../OpenGL/GLIncludes.h"
#include "../OpenGL/GLUtils.h"
#include "../Rendering/RenderSystem.h"
#include "../Input/InputManager.h"
#include <time.h>
#include <iostream>
#include "../Sound/AudioSystem.h"
#include "../Game/StateLevelOne.h"
#include "../Foundation/Foundation.h"

using namespace std;

int main(void)
{
	InputManager* inputSystem = new InputManager(RenderSystem::GetSingleton()->mWindow);

	AudioSystem* audioSystem = new AudioSystem();
	audioSystem->Initialise();

	//audioSystem->PlaySound("Tank.mp3");

	StateLevelOne* stateLevelOne = new StateLevelOne();

	double olddelta = 0;
	double delta = 0;
	double begin_time = glfwGetTime();

	float time = 0;

	// Loop until the window should close
	while (!glfwWindowShouldClose(RenderSystem::GetSingleton()->mWindow))
	{
		delta = glfwGetTime() - olddelta;
		olddelta = glfwGetTime();

		time += delta;

		if(time > 1)
		{
			time = 0;
			//cout << "DeltaTime: " << delta << endl;
		}

		inputSystem->Update(delta);

		stateLevelOne->Update(delta);

		RenderSystem::GetSingleton()->Draw();

		glfwSwapBuffers(RenderSystem::mWindow);

		// Check for new events
		glfwPollEvents();
	}

	SAFE_DELETE(inputSystem);
	SAFE_DELETE(audioSystem);
	SAFE_DELETE(stateLevelOne);

	glfwDestroyWindow(RenderSystem::GetSingleton()->mWindow);
	glfwTerminate();

	return 0;
}