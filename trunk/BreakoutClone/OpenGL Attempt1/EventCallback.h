#ifndef EVENT_CALLBACK_SIMENGINE
#define EVENT_CALLBACK_SIMENGINE

#include "Foundation.h"
#include <iostream>

// =======================================
// BASE FUNCTION CALLBACK CLASS
// =======================================
class IEventCallback
{
public:
	virtual void operator() (uint inEventType) = 0;
};

// =======================================
// MEMBER FUNCTION CALLBACK CLASS
// =======================================
template <class ClassType>
class EventCallbackMember : public IEventCallback
{
public:
	EventCallbackMember(ClassType* inClassPointer, void (ClassType::*inEventCallbackFunc)(uint));
	void operator() (uint inEventType);

public:
	void (ClassType::*mEventCallbackFunc)(uint);
	ClassType* mClassPointer;
};

template <class ClassType>
EventCallbackMember<ClassType>::EventCallbackMember(ClassType* inClassPointer, void (ClassType::*inEventCallbackFunc)(uint)) : 
mClassPointer(inClassPointer),
mEventCallbackFunc(inEventCallbackFunc)
{
	assert(mClassPointer && mEventCallbackFunc);
}

template <class ClassType>
void EventCallbackMember<ClassType>::operator() (uint inEventType)
{
	std::cout << "\nMember function callback\n";
	(mClassPointer->*mEventCallbackFunc)(inEventType);
}

// =======================================
// FREE FUNCTION CALLBACK CLASS
// =======================================
class EventCallbackFree : public IEventCallback
{
public:
	EventCallbackFree(void (*inEventCallbackFunc)(uint));
	void operator() (uint inEventType);

public:
	void (*mEventCallbackFunc)(uint);
};

#endif //include guard