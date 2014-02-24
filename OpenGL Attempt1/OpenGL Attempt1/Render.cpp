#include "Render.h"

Render::Render()
{

}

Render::~Render()
{

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

void Render::Draw()
{
	for(int i = 0; i < mEntities.size() ; ++i)
	{
		mEntities[i]->Draw();
	}
}