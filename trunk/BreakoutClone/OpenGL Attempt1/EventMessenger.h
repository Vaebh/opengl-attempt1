#ifndef EVENT_MESSENGER_SIMENGINE
#define EVENT_MESSENGER_SIMENGINE

#include "Component.h"

enum EventTypes
{
	PLAYER_MOVE,
	NUM_EVENTS
};

/*struct Message
{
	std::string messageID;
	MessageDelegate inDelegate;
};*/

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
	std::vector<std::vector<EventType or something>> mEvents;
};

#endif