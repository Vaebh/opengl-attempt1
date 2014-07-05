#include "GameObject.h"
#include <algorithm>

unsigned int GameObject::mNumGameObjects = 0;

GameObject::GameObject() :
mIndex(mNumGameObjects++),
mPosition(0),
mScale(1.0, 1.0, 1.0),
mRotationAngle(0),
mVelocity(0)
{

}

GameObject::~GameObject()
{
	for each(IComponent* theComponent in mComponents)
	{
		delete theComponent;
	}

	mComponents.clear();
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
	inComponent->OnAttached(this);
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

void GameObject::MovePosition(Vector3 inPosition)
{
	inPosition = GetPosition() + inPosition;

	for each(IComponent* theComponent in mComponents)
	{
		theComponent->PrePositionSet(inPosition);
	}

	SetPosition(inPosition);
}

void GameObject::Update(float inDT)
{
	MovePosition(mVelocity * inDT);

	for(std::vector<IComponent*>::const_iterator it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if(*it)
		{
			(*it)->Update(inDT);
		}
	}
}