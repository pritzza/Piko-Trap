#pragma once

#include "../util/AABB.h"

#include <SFML/System/Vector2.hpp>

class Body2D
{
private:
	AABB body;

public:
	void setPos(const sf::Vector2f& pos);
	void setDim(const sf::Vector2f& dim);
};