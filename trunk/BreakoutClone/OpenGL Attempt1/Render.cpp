#include "Render.h"

Render* Render::mRenderer = 0;

GLFWwindow* Render::mWindow;

GLFWwindow* InitialiseWindow()
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
}

Render::Render()
{
	if(!mWindow)
	{
		mWindow = InitialiseWindow();
	}
}

Render::~Render()
{

}

Render* Render::GetSingleton()
{
	if(!mRenderer)
	{
		mRenderer = new Render();
	}

	return mRenderer;
}

void Render::SetFrameBufferTarget(GLuint inFrameBuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, inFrameBuffer);
}

void Render::AddEntity(Entity* inEntity)
{
	if(inEntity)
	{
		mEntities.push_back(inEntity);
	}
}

void Render::RemoveEntity(Entity* inEntity)
{
	if(inEntity)
	{
		std::vector<Entity*>::const_iterator iter;

		for(iter = mEntities.begin(); iter != mEntities.end(); ++iter)
		{
			if(*iter == inEntity)
			{
				mEntities.erase(iter);
				break;
			}
		}
	}
}

void Render::Draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	for(int i = 0; i < mEntities.size() ; ++i)
	{
		if(mEntities[i]->IsVisible())
		{
			mEntities[i]->Draw();
		}
	}
}