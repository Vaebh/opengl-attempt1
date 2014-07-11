#ifndef EVENT_MESSENGER_SIMENGINE
#define EVENT_MESSENGER_SIMENGINE

#include "Component.h"

// Hold a vector/map of pairs, which each hold a string event id, and a vector of function pointers
// This approach hinges on being able to compare function pointers. So when we subscribe to an event we
// just check the event against the list of event id's and add the supplied function pointer to it's paired vector of function pointers

/* e.g.
vector<pair(string eventID, vector<functionPointers>)> eventList
for(eventList)
{
	if(suppliedEventID == eventList[i].first)
	{
		eventList[i].second.push_back(suppliedFunctionPointer);
	}
}
*/

/* And when you unsubscribe you just check through the eventList for your matching eventID and function pointer
/* e.g.
vector<pair(string eventID, vector<functionPointers>)> eventList
for(eventList)
{
	if(suppliedEventID == eventList[i].first)
	{
		for(functionPointerList)
		{
			if(suppliedFunctionPointer == functionPointerList[j])
			{
				functionPointerList[j].remove();
			}
		}
	}
}
*/

// Read in the string eventList from a file, make sure to have a SetEventListFile method so we can
// set which file is on a per application basis.



// Iffy on whether to use an enum, kind of want to just use raw strings so the messages can be more variable
// Maybe just hold a list of pairs comprised of listeners and what events they're subscribed to and invoke them if the
// received message matches their subscirbed one
enum EventTypes
{
	PLAYER_MOVE,
	NUM_EVENTS
};

// I don't know about this yet
struct MessageHolder
{
	EventTypes mMessageType;
	std::vector<MessageDelegate> mDelegates;
};

typedef void (*MessageDelegate)(std::string);

// Have things able to just #include this file and then subscribe themselves to specific events
// They supply a function pointer to a function that the event messaging system will call when an event of that type shows up
// Will likely declare this function pointer as a virtual function in either GameObject or Component, though any file
// can subscribe to any event and provide their own custom function pointer

// Actually will likely not put it in GameObject or Component, better to keep it only in the classes that need it
// Maybe make an interface to inherit from that provides a couple of methods for receiving events and subscribing to them

// Could also put in delayed events with an update method

class IEventMessenger
{
public:
	// Might not need this one
	virtual void SendMessage(const std::string& inMessage) = 0;

	// Loop through list of events and call function pointers for ones that match the recorded event - possibly 2d vector?
	void RecordEvent(EventTypes inEventType, float inEventNotificationDelay = 0.f);

	static void SubscribeToEvent(EventTypes inEventType, MessageDelegate inMsgDel);
	static void UnsubscribeToEvent(EventTypes inEventType, MessageDelegate inMsgDel);

	void Update(float inDT);

private:
	std::vector<MessageHolder> mEvents;
};

#endif