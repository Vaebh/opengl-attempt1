#include "EventCallback.h"
#include <assert.h>

EventCallbackFree::EventCallbackFree(void (*inEventCallbackFunc)(uint32_t)) : 
mEventCallbackFunc(inEventCallbackFunc)
{
	assert(mEventCallbackFunc);
}

void EventCallbackFree::operator() (uint32_t inEventType)
{
	std::cout << "\nFree function callback\n";
	mEventCallbackFunc(inEventType);
}