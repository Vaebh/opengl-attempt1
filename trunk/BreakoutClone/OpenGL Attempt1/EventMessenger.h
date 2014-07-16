#ifndef EVENT_MESSENGER_SIMENGINE
#define EVENT_MESSENGER_SIMENGINE

#include "Component.h"
#include "Foundation.h"
#include "EventCallback.h"

// The main problem with this system right now is there's no way to subscribe the events of specific components or gameobjects
// For example I could want to listen to the collision event of a specific BounceComponent, the one attached to the ball in a Breakout game
// However all I can do right now is listen for ALL collision events

// One way is to pass in pointers to specific components, but that constrains the events so they can only be used in components, not anywhere I please

// Really the issue is that I want to listen to the things (events) that occur to specific things
// So I want to listen to the OnCollision event of the ball, but nothing else
// The only way I can think of to do that would be to store a pointer to the object that I want to listen to

enum EventType
{
	BALL_COLLISION,
	NUM_EVENTS
};

typedef IEventCallback* MessageDelegate;

struct Event
{
	uint32_t mEventType;
	std::vector<MessageDelegate> mEventDelegates;
};

class EventMessenger
{
public:
	EventMessenger();

	static EventMessenger* GetSingleton();

	// Will have to add another parameter for passing event specific info, an array of string or uint params maybe
	void RecordEvent(uint32_t inEventType, float inEventNotificationDelay = 0.f);

	void SubscribeToEvent(uint32_t inEventType, MessageDelegate inMsgDel);
	void UnsubscribeToEvent(uint32_t inEventType, MessageDelegate inMsgDel);

	// TODO - Add delayed events, will likely need an event queue
	//void Update(float inDT);

private:
	std::vector<Event> mEvents;

	static EventMessenger* mEventMessenger;
};

#endif