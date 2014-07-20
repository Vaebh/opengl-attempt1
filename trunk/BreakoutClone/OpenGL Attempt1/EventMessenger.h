#ifndef EVENT_MESSENGER_SIMENGINE
#define EVENT_MESSENGER_SIMENGINE

#include "Component.h"
#include "Foundation.h"
#include "EventCallback.h"
#include <utility>

// The main problem with this system right now is there's no way to subscribe the events of specific components or gameobjects
// For example I could want to listen to the collision event of a specific BounceComponent, the one attached to the ball in a Breakout game
// However all I can do right now is listen for ALL collision events

// One way is to pass in pointers to specific components, but that constrains the events so they can only be used in components, not anywhere I please

// Really the issue is that I want to listen to the things (events) that occur to specific things
// So I want to listen to the OnCollision event of the ball, but nothing else
// The only way I can think of to do that would be to store a pointer to the object that I want to listen to

enum EventType
{
	COLLISION,
	INPUT_LEFT_CLICK,
	INPUT_LEFT_RELEASE,
	INPUT_RIGHT_CLICK,
	INPUT_RIGHT_RELEASE,
	INPUT_SPACE_PRESS,
	INPUT_SPACE_RELEASE,
	INPUT_W_PRESS,
	INPUT_W_RELEASE,
	INPUT_A_PRESS,
	INPUT_A_RELEASE,
	INPUT_S_PRESS,
	INPUT_S_RELEASE,
	INPUT_D_PRESS,
	INPUT_D_RELEASE,
	NUM_EVENTS
};

typedef IEventCallback* MessageDelegate;
typedef std::pair<GameObject*, MessageDelegate> EventPair;

// Should maybe be a map of pairs - pair<EventID id, GameObject* target>, with the data being a vector of message delegates
// This might make it more difficult to send a complete event message when it comes time to do networking
// Should at least be a collection of message delegates per GameObject* as the same object could have multiple things subscribed to it
struct Event
{
	uint32_t mEventType;
	std::vector<EventPair> mEventTargets;
};

class EventMessenger
{
public:
	EventMessenger();

	static EventMessenger* GetSingleton();

	// Will have to add another parameter for passing event specific info, an array of string or uint params maybe
	void RecordEvent(uint32_t inEventType, GameObject* inTarget, float inEventNotificationDelay = 0.f);
	void BroadcastEvent(uint32_t inEventType, float inEventNotificationDelay = 0.f);

	void SubscribeToEvent(uint32_t inEventType, GameObject* inTarget, MessageDelegate inMsgDel);
	void UnsubscribeToEvent(uint32_t inEventType, GameObject* inTarget, MessageDelegate inMsgDel);

	// TODO - Add delayed events, will likely need an event queue
	//void Update(float inDT);

private:
	std::vector<Event> mEvents;

	static EventMessenger* mEventMessenger;
};

#endif