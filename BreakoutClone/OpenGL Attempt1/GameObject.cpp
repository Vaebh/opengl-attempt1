#include "GameObject.h"
#include <algorithm>

unsigned int GameObject::mNumGameObjects = 0;

GameObject::GameObject() :
mIndex(mNumGameObjects++)
,mVelocity()
{

}

void GameObject::Attach(IComponent* inComponent)
{
	for(std::vector<IComponent*>::const_iterator it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		// Check if we have this Component
		if((*it) == inComponent)
		{
			return;
		}
	}

	inComponent->SetOwner(this);
	mComponents.push_back(inComponent);
}

void GameObject::Detach(IComponent* inComponent)
{
	if(inComponent == NULL)
		return;

	for(std::vector<IComponent*>::const_iterator it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		// Check if we have this Component
		if((*it) == inComponent)
		{
			inComponent->SetOwner(NULL);
			mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), inComponent));
			break;
		}
	}
}

void GameObject::Update(float inDT)
{
	/*for(std::vector<IComponent*>::const_iterator it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if(*it)
		{
			(*it)->Update(inDT);
		}
	}*/
}