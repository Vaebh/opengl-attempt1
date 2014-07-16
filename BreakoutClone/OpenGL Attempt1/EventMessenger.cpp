#include "EventMessenger.h"

// TODO
// Switch all the loops in all methods to work like the one in SubscribeToEvent - as I am dumb
// and forgot that there were no pointers so I had to directly access and change the values

// With that in mind will probably change mEvents to store pointers to Events, not just Events

// Also have to work out how to pass class functions via function pointers, or if that's even possible without
// making the function pointer specific to that class

// Also look into making the enum list expandable, I want to be able to define more events outside of this header file via the
// comments I put in EventMessenger.h. With that in mind I should change the delegate to take unsigned ints, not EventTypes

EventMessenger* EventMessenger::mEventMessenger;

namespace
{
	// Make a function for squashing the eventList down to size again
}

EventMessenger::EventMessenger()
{
	Event newEvent;

	mEvents.reserve(NUM_EVENTS);
	for(unsigned int i = 0; i < NUM_EVENTS; ++i)
	{
		newEvent.mEventType = EventType(i);

		mEvents.push_back(newEvent);
	}
}

EventMessenger* EventMessenger::GetSingleton()
{
	if(!mEventMessenger)
	{
		mEventMessenger = new EventMessenger();
	}

	return mEventMessenger;
}

void EventMessenger::RecordEvent(uint32_t inEventType, float inEventNotificationDelay)
{
	std::vector<Event> events = GetSingleton()->mEvents;

	for each(Event theEvent in events)
	{
		if(theEvent.mEventType == inEventType)
		{
			for each(MessageDelegate theDelegate in theEvent.mEventDelegates)
			{
				if(theDelegate != NULL)
				{
					(*theDelegate)(inEventType);
				}
			}
		}
	}
}

// Loop through event list, if the delegate is null or already there then return,
// otherwise add it to the delegate list
void EventMessenger::SubscribeToEvent(uint32_t inEventType, MessageDelegate inMsgDel)
{
	if(inMsgDel == NULL)
		return;

	//std::vector<Event>* events = &GetSingleton()->mEvents;

	for(unsigned int i = 0; i < mEvents.size(); ++i)
	{
		if(mEvents[i].mEventType == inEventType)
		{
			for(unsigned int j = 0; j < mEvents[i].mEventDelegates.size(); ++j)
			{
				if(mEvents[i].mEventDelegates[j] == inMsgDel)
				{
					return;
				}
			}

			mEvents[i].mEventDelegates.push_back(inMsgDel);
			return;
		}
	}

	// If this event is not in the list then add it
	Event newEvent;
	newEvent.mEventType = inEventType;
	newEvent.mEventDelegates = std::vector<MessageDelegate>();
	newEvent.mEventDelegates.push_back(inMsgDel);

	mEvents.push_back(newEvent);
}

// Loop through event list, if the delegate is null or not there then return,
// otherwise remove it from the delegate list
void EventMessenger::UnsubscribeToEvent(uint32_t inEventType, MessageDelegate inMsgDel)
{
	if(inMsgDel == NULL)
		return;

	for each(Event theEvent in GetSingleton()->mEvents)
	{
		if(theEvent.mEventType == inEventType)
		{
			for each(MessageDelegate theDelegate in theEvent.mEventDelegates)
			{
				if(theDelegate == inMsgDel)
				{
					inMsgDel = 0;
					return;
				}
			}

			// The delegate isn't here
			return;
		}
	}
}