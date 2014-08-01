#include "../Rendering/RenderSystem.h"
#include "../Rendering/Shader.h"
#include <iostream>

RenderSystem* RenderSystem::mRenderer = NULL;

GLFWwindow* RenderSystem::mWindow;

static void ErrorCallback(int error, const char* description)
{
    std::cout<< "GLFW ERROR: " << description << std::endl;
}

namespace
{
	// Should move this to somewhere more appropriate, Application.cpp maybe?
	GLFWwindow* InitialiseWindow()
	{
		if (!glfwInit())
			return NULL;
        
        glfwSetErrorCallback(ErrorCallback);
    
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow* window = glfwCreateWindow(640, 480, "Breakout Clone", NULL, NULL);
        
		if(!window)
		{
			glfwTerminate();
            return NULL;
		}
  
		glfwMakeContextCurrent(window);

		glViewport(0, 0, 640, 480);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 640, 480, 0, -640, 640);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glewExperimental = GL_TRUE;
		glewInit();

		return window;
	}
}

RenderSystem::RenderSystem()
{
	if(!mWindow)
	{
		mWindow = InitialiseWindow();
	}
}

RenderSystem::~RenderSystem()
{

}

RenderSystem* RenderSystem::GetSingleton()
{
	if(!mRenderer)
	{
		mRenderer = new RenderSystem();
	}

	return mRenderer;
}

void RenderSystem::SetFrameBufferTarget(GLuint inFrameBuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, inFrameBuffer);
}

// These two methods should be abstract in System.h
void RenderSystem::AddComponent(IRenderableComponent* inRenderableComponent)
{
	if(inRenderableComponent)
	{
		mComponents.push_back(inRenderableComponent);
	}
}

void RenderSystem::RemoveComponent(IRenderableComponent* inRenderableComponent)
{
	if(inRenderableComponent)
	{
		std::vector<IRenderableComponent*>::const_iterator it;

		for(it = mComponents.begin(); it != mComponents.end(); ++it)
		{
			if((*it) == inRenderableComponent)
			{
				mComponents.erase(it);

				// Downsize the vector
				std::vector<IRenderableComponent*>(mComponents).swap(mComponents);
				break;
			}
		}
	}
}

void RenderSystem::Update(float inDT)
{
	/*for(std::vector<IRenderableComponent*>::const_iterator it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if(*it)
		{
			(*it)->Update(inDT);
		}
	}*/
}

void RenderSystem::Draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int numVertices = 0;

	Shader* spriteShader = NULL;

	glActiveTexture(GL_TEXTURE0);

	for(int i = 0; i < mComponents.size(); ++i)
	{
		if(mComponents[i]->IsVisible())
		{
			if(spriteShader == NULL)
			{
				spriteShader = mComponents[i]->GetShader();
				glUseProgram(spriteShader->GetProgramID());
			}

			mComponents[i]->Draw();

			glDrawArrays(GL_TRIANGLES, 0, 6);

			numVertices += 6;
		}
	}

	//glDrawArrays(GL_TRIANGLES, 0, numVertices);
}