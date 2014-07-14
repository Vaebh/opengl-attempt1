#include "EventCallback.h"
#include <assert.h>

EventCallbackFree::EventCallbackFree(void (*inEventCallbackFunc)(uint)) : 
mEventCallbackFunc(inEventCallbackFunc)
{
	assert(mEventCallbackFunc);
}

void EventCallbackFree::operator() (uint inEventType)
{
	std::cout << "\nFree function callback\n";
	mEventCallbackFunc(inEventType);
}