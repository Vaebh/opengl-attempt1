#include "Render.h"

Render* Render::mRenderer = 0;

Render::Render()
{

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