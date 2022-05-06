#pragma once

#include "Event.h"

#include "../entity/Entity.h"

struct EntityCollisionEvent : public Event
{
	Entity& e1;
	Entity& e2;

	EntityCollisionEvent(Entity& e1, Entity& e2) 
		:
		e1{ e1 },
		e2{ e2 }
	{}
};