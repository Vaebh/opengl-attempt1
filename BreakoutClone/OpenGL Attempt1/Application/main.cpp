#include "../Foundation/Foundation.h"

#include "../OpenGL/GLIncludes.h"
#include "../OpenGL/GLUtils.h"

#include "../Input/InputManager.h"
#include "../Rendering/RenderSystem.h"
#include "../Sound/AudioSystem.h"

#include "../Game/StateLevelOne.h"
#include "../Structure/StateManager.h"

#include <iostream>

using namespace std;

int main(void)
{
    const int years = 10;
    int savings = 0;
    float investmentReturn = 0.04;
    
    float savedIncomePerMonth = 5000.f;
    float yearlyIncome = savedIncomePerMonth * 12;
    
    for(int i = 1; i <= years; ++i)
    {
        if(savings > 3000)
            savings += savings * investmentReturn;
        
        savings += yearlyIncome;
        
        cout << "year " << i << " savings: " << savings << endl;
    }
    
	InputManager* inputSystem = new InputManager(RenderSystem::GetSingleton()->mWindow);

	AudioSystem* audioSystem = new AudioSystem();
	audioSystem->Initialise();

	audioSystem->PlayMusic("Tank.mp3");

	StateManager* stateManager = new StateManager(new StateLevelOne());

	double olddelta = 0;
	double delta = 0;

	float fpsTimer = 0;

	bool stateChange = false;
	float timer = 0;

	// Loop until the window should close
	while (!glfwWindowShouldClose(RenderSystem::GetSingleton()->mWindow))
	{
		delta = glfwGetTime() - olddelta;
		olddelta = glfwGetTime();

		fpsTimer += delta;

		if(fpsTimer > 0.2)
		{
			fpsTimer = 0;
			//cout << "DeltaTime: " << delta << endl;
			//cout << "FPS: " << 1 / delta << endl;
		}

		// Stupid test code
		if(glfwGetKey(RenderSystem::GetSingleton()->mWindow, GLFW_KEY_BACKSPACE) == GLFW_PRESS && stateChange == false)
		{
			stateChange = true;
			timer = 0;

			stateManager->PopState();
			stateManager->PushState(new StateLevelOne());
		}

		if(stateChange)
			timer += delta;

		if(timer >= 1)
			stateChange = false;
		// End of stupid test code

		inputSystem->Update(delta);

		stateManager->Update(delta);

		RenderSystem::GetSingleton()->Draw();

		glfwSwapBuffers(RenderSystem::mWindow);

		// Check for new events
		glfwPollEvents();
	}

	SAFE_DELETE(inputSystem);
	SAFE_DELETE(audioSystem);
	SAFE_DELETE(stateManager);

	glfwDestroyWindow(RenderSystem::GetSingleton()->mWindow);
	glfwTerminate();

	return 0;
}