#pragma once

#include <iostream>

class EntityCollisionEvent;

class PhysicsHandler
{
public:
	void handleEntityCollision(EntityCollisionEvent* e)
	{
		std::cout << "AHHHH COLLISION!!!\n";
	}
};