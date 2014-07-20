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

void EventMessenger::RecordEvent(uint32_t inEventType, GameObject* inTarget, float inEventNotificationDelay)
{
	for each(Event theEvent in mEvents)
	{
		if(theEvent.mEventType == inEventType)
		{
			for each(EventPair theEventPair in theEvent.mEventTargets)
			{
				// If the recorded gameobject matches the stored gameobject
				if(theEventPair.first != NULL && theEventPair.first == inTarget)
				{
					(*theEventPair.second)(inEventType, theEventPair.first);
					break;
				}
			}
		}
	}
}

void EventMessenger::BroadcastEvent(uint32_t inEventType, float inEventNotificationDelay)
{
	for each(Event theEvent in mEvents)
	{
		if(theEvent.mEventType == inEventType)
		{
			for each(EventPair theEventPair in theEvent.mEventTargets)
			{
				(*theEventPair.second)(inEventType, NULL);
			}
		}
	}
}

// Loop through event list, if the delegate is null or already there then return,
// otherwise add it to the delegate list
void EventMessenger::SubscribeToEvent(uint32_t inEventType, GameObject* inTarget, MessageDelegate inMsgDel)
{
	if(inMsgDel == NULL || inTarget == NULL)
		return;

	for(unsigned int i = 0; i < mEvents.size(); ++i)
	{
		if(mEvents[i].mEventType == inEventType)
		{
			for(unsigned int j = 0; j < mEvents[i].mEventTargets.size(); ++j)
			{
				if(mEvents[i].mEventTargets[j].first == inTarget || mEvents[i].mEventTargets[j].second == inMsgDel)
				{
					// If it's the same GameObject that we're subscribing to then just add the message delegate
					// to that GameObjects vector of MessageDelegates, once it's implemented
					//return;
				}
			}

			mEvents[i].mEventTargets.push_back(std::make_pair(inTarget, inMsgDel));
			return;
		}
	}

	// If this event is not in the list then add it
	Event newEvent;
	newEvent.mEventType = inEventType;
	newEvent.mEventTargets = std::vector<EventPair>();
	newEvent.mEventTargets.push_back(std::make_pair(inTarget, inMsgDel));

	mEvents.push_back(newEvent);
}

// Loop through event list, if the delegate is null or not there then return,
// otherwise remove it from the delegate list
void EventMessenger::UnsubscribeToEvent(uint32_t inEventType, GameObject* inTarget, MessageDelegate inMsgDel)
{
	if(inMsgDel == NULL || inTarget == NULL)
		return;

	for each(Event theEvent in GetSingleton()->mEvents)
	{
		if(theEvent.mEventType == inEventType)
		{
			for each(EventPair theEventPair in theEvent.mEventTargets)
			{
				if(theEventPair.first == inTarget && theEventPair.second == inMsgDel)
				{
					// Should actually remove these from the vector
					theEventPair.first = 0;
					theEventPair.second = 0;
					return;
				}
			}

			// The delegate isn't here
			return;
		}
	}
}