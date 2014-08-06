#include "../Structure/StateManager.h"
#include "../Foundation/Foundation.h"
#include <iostream>

StateManager::StateManager(IState* const inInitialState)
{
	PushState(inInitialState);
}

StateManager::~StateManager()
{
	while(!mStateHierarchy.empty())
	{
		SAFE_DELETE(mStateHierarchy.back());
		mStateHierarchy.pop_back();
	}

	mActiveState = NULL;
}

void StateManager::PushState(IState* const inNewState)
{
	mStateHierarchy.push_back(inNewState);
	mActiveState = inNewState;
}

void StateManager::PopState()
{
	if(mStateHierarchy.empty())
		return;

	SAFE_DELETE(mStateHierarchy.back());
	mStateHierarchy.pop_back();

	if(!mStateHierarchy.empty())
		mActiveState = mStateHierarchy.back();
	else
		mActiveState = NULL;
}

const IState* StateManager::GetActiveState() const
{
	return mStateHierarchy.back();
}

void StateManager::Update(float inDT)
{
	if(mActiveState != NULL)
		mActiveState->Update(inDT);
}