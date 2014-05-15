#include "GLIncludes.h"
#include "GLUtils.h"
#include "Shader.h"
#include "Sprite.h"
#include "Render.h"
#include "Input.h"
#include <time.h>
#include <iostream>
#include "Scene.h"
#include "AudioSystem.h"
#include "Ball.h"
#include "Block.h"
#include "StateLevelOne.h"

#include <fmod.hpp>
#include <fmod_errors.h>
using namespace std;

/*GLFWwindow* InitialiseWindow()
{
	if (!glfwInit())
		return NULL;
    
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Breakout Clone", NULL, NULL);
  
	if (!window)
	{
		glfwTerminate();
			return NULL;
	}
  
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	return window;
}*/

int main(void)
{
	// Initialise the window
	//GLFWwindow* window = InitialiseWindow();

	//if(!window)
		//return 1;

	Sprite* puppy = NULL;
	Sprite* kitten = NULL;

	Scene* theScene = new Scene();

	/*kitten = new Sprite("bros.png");
	Input* inputHandler = new Input(window, kitten);
	kitten->SetPosition(Vector3(0.4, -0.4, 0));
	kitten->mScale = Vector3(0.5, 0.5, 0);

	puppy = new Sprite("sample2.png");
	puppy->SetPosition(Vector3(0.8, 0.5, 0));
	puppy->mScale = Vector3(0.5, 0.5, 0);

	theScene->AddToScene(kitten);
	theScene->AddToScene(puppy);*/

	AudioSystem* audioSystem = new AudioSystem();
	audioSystem->Initialise();

	//audioSystem->PlaySound("Tank.mp3");

	StateLevelOne* levelOne = new StateLevelOne(theScene);

	double olddelta = 0;
	double delta = 0;
	double begin_time = glfwGetTime();

	/*Ball* ball = new Ball();
	ball->SetPosition(Vector3(-0.2, 0.5, 0));
	ball->mScale = Vector3(0.1, 0.1, 0);

	theScene->AddToScene(ball);

	Block* block = new Block();
	block->SetPosition(Vector3(-0.2, -0.5, 0));
	block->mScale = Vector3(0.3, 0.15, 0);

	theScene->AddToScene(block);*/

	// Loop until the window should close
	while (!glfwWindowShouldClose(Render::GetSingleton()->mWindow))
	{
		delta = glfwGetTime() - olddelta;
		olddelta = glfwGetTime();

		levelOne->Update(delta);

		/*if(block && block->mHealth <= 0)
		{
			delete block;
			block = 0;
		}*/

		theScene->Update(delta);

		Render::GetSingleton()->Draw();

		glfwSwapBuffers(Render::mWindow);

		// Check for new events
		glfwPollEvents();
	}

	//delete kitten;
	//kitten = 0;

	glfwDestroyWindow(Render::GetSingleton()->mWindow);
	glfwTerminate();

	return 0;
}