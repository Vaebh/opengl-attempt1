#include "Render.h"
#include "Shader.h"

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

	int numVertices = 0;

	Shader* spriteShader = NULL;

	glActiveTexture(GL_TEXTURE0);

	for(int i = 0; i < mEntities.size() ; ++i)
	{
		if(mEntities[i]->IsVisible())
		{
			if(spriteShader == NULL)
			{
				spriteShader = mEntities[i]->mShader;
				glUseProgram(spriteShader->GetProgramID());
			}

			mEntities[i]->Draw();

			glDrawArrays(GL_TRIANGLES, 0, 6);

			numVertices += 6;
		}
	}

	//glDrawArrays(GL_TRIANGLES, 0, numVertices);
}