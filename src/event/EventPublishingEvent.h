#pragma once

#include "EventBus.h"

struct EventPublishingEvent : Event
{
protected:
	const EventBus& bus;	// stores a reference to the event bus
							// so events can publish other events

	EventPublishingEvent(const EventBus& bus)
		:
		bus{ bus }
	{}
};